/* GNE - Game Networking Engine, a portable multithreaded networking library.
 * Copyright (C) 2001 Jason Winnebeck (gillius@mail.rit.edu)
 * Project website: http://www.rit.edu/~jpw9607/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "../include/gnelib/gneintern.h"
#include "../include/gnelib/PacketStream.h"
#include "../include/gnelib/Packet.h"
#include "../include/gnelib/PacketFeeder.h"
#include "../include/gnelib/Connection.h"
#include "../include/gnelib/Buffer.h"
#include "../include/gnelib/RateAdjustPacket.h"
#include "../include/gnelib/ExitPacket.h"
#include "../include/gnelib/PacketParser.h"
#include "../include/gnelib/Time.h"
#include "../include/gnelib/Timer.h"
#include "../include/gnelib/Errors.h"
#include "../include/gnelib/Lock.h"

const int BUF_LEN = 1024;

//This is the timestep size for the rate control in microseconds.
//The current step is 1/10 of a second which allows for a rate granularity of
//10 bps.
const int TIME_STEP = 100000;
const int TIME_STEPS_PER_SEC = 1000000 / TIME_STEP;

namespace GNE {

PacketStream::PacketStream(int reqOutRate, int maxOutRate, Connection& ourOwner)
: Thread("PktStrm", Thread::HIGH_PRI), owner(ourOwner), maxOutRate(maxOutRate),
reqOutRate(reqOutRate), feederAllowed(true), feederTimeout(0),
lowPacketsThreshold(0) {
  assert(reqOutRate >= 0);
  assert(maxOutRate >= 0);

  setType( CONNECTION );

  //Calculate the current rate and step.
  setupCurrRate();

  //Set the amount we can send without waiting to the max.
  outRemain = currOutRate;

  //Set the last calculation time:
  lastTime = Timer::getCurrentTime();

  gnedbgo2(2, "PacketStream negotiated: max: %d requested: %d",
    maxOutRate, reqOutRate);
  gnedbgo(5, "created");
}

PacketStream::sptr PacketStream::create(int reqOutRate, int maxOutRate, Connection& ourOwner) {
  sptr ret( new PacketStream( reqOutRate, maxOutRate, ourOwner ) );
  ret->setThisPointer( ret );
  return ret;
}

PacketStream::~PacketStream() {
  //We can't do assert(shutdown) in case PacketStream was never started.
  assert(!isRunning());

  //Clear out our queues.
  Packet* temp = NULL;

  //Empty out the outgoing queues.
  outQCtrl.acquire();
  while (!outRel.empty()) {
    delete outRel.front();
    outRel.pop();
  }
  while (!outUnrel.empty()) {
    delete outUnrel.front();
    outUnrel.pop();
  }
  outQCtrl.release();

  //Empty the incoming queue.
  while ((temp = getNextPacket()) != NULL)
    delete temp;

  gnedbgo(5, "destroyed");
}

int PacketStream::getInLength() const {
  LockMutex lock( inQCtrl );
  return in.size();
}

int PacketStream::getOutLength(bool reliable) const {
  LockCV lock( outQCtrl );
  return reliable ? outRel.size() : outUnrel.size();
}

void PacketStream::setFeeder(const PacketFeeder::sptr& newFeeder) {
  LockCV lock( outQCtrl );
  if ( feederAllowed ) {
    feeder = newFeeder;
  
    //The broadcasts in this function and the next few are to wake up the
    //thread so it will reevaluate if it will generate an onLowPackets event.
    outQCtrl.broadcast();
  }
}

void PacketStream::setLowPacketThreshold(int limit) {
  lowPacketsThreshold = limit;
  outQCtrl.broadcast();
}

int PacketStream::getLowPacketThreshold() const {
  return lowPacketsThreshold;
}

void PacketStream::setFeederTimeout(int ms) {
  assert(ms >= 0);

  //Do nothing on invalid input.
  if (ms >= 0) {
    feederTimeout = ms;
    outQCtrl.broadcast();
  }
}

int PacketStream::getFeederTimeout() const {
  return feederTimeout;
}

bool PacketStream::isNextPacket() const {
  return (getInLength() != 0);
}

Packet* PacketStream::getNextPacket() {
  Packet* ret = NULL;
  inQCtrl.acquire();
  if (!in.empty()) {
    ret = in.front();
    in.pop();
  }
  inQCtrl.release();
  return ret;
}

Packet::sptr PacketStream::getNextPacketSp() {
  return Packet::sptr( getNextPacket(), PacketParser::destroyPacket );
}

void PacketStream::writePacket(const Packet& packet, bool reliable) {
  //Perform operations on the outgoing queue
  outQCtrl.acquire();
  bool notify = false;
  if (reliable) {
    notify = outRel.empty();
    outRel.push(packet.makeClone());
  } else {
    notify = outUnrel.empty();
    outUnrel.push(packet.makeClone());
  }
  outQCtrl.release();

  //If we need to, wake up the writer thread.
  if (notify)
    outQCtrl.broadcast();
}

void PacketStream::writePacket(const Packet::sptr& packet, bool reliable) {
  writePacket( *packet, reliable );
}

int PacketStream::getCurrOutRate() const {
  return currOutRate;
}

int PacketStream::getReqOutRate() const {
  return reqOutRate;
}

int PacketStream::getRemoteOutLimit() const {
  return maxOutRate;
}

void PacketStream::setRates(int reqOutRate2, int maxInRate2) {
  if (reqOutRate2 >= 0) {
    outQCtrl.acquire();
    reqOutRate = reqOutRate2;
    setupCurrRate();
    outQCtrl.release();
  }

  //Now handle the inRate changes, sending a notice if needed.
  if (maxInRate2 >= 0) {
    RateAdjustPacket notice;
    notice.rate = maxInRate2;
    writePacket(notice, true);
  }
}

void PacketStream::waitToSendAll(int waitTime) const {
  assert(waitTime <= (INT_MAX / 1000));
  assert(waitTime > 0);

  Time t = Timer::getCurrentTime();
  Time waitUntil = t + (waitTime * 1000);
  bool timeOut = (waitTime <= 0);
  int ms = waitTime;

  outQCtrl.acquire();
  while ((!outRel.empty() || !outUnrel.empty()) && !shutdown && !timeOut) {
    outQCtrl.timedWait(ms);

    t = Timer::getCurrentTime();
    timeOut = (t > waitUntil);
    ms = (t - waitUntil).getTotaluSec() / 1000;
  }
  outQCtrl.release();
}

void PacketStream::shutDown() {
  Thread::shutDown();
  //We acquire the mutex to avoid the possiblity of a deadlock between the
  // test for the shutdown variable and the wait.
  outQCtrl.acquire();
  outQCtrl.broadcast();
  outQCtrl.release();
}

/**
 * \bug  we need a way to guarantee that the write won't block when trying
 *       to send the ExitPacket on shutdown.
 */
void PacketStream::run() {
  int numPackets = 0;

  outQCtrl.acquire();
  while (!shutdown) {
    //Check the numpackets and call the feeder if needed.
    numPackets = (int)(outRel.size() + outUnrel.size());

    if (numPackets > 0) {
      //Trigger the onLowPackets event if needed
      onLowPackets(numPackets);

    } else {
      //Waiting loop for when there are no packets
      while (numPackets == 0 && !shutdown) {
        //Notify any threads waiting on waitToSendAll
        outQCtrl.broadcast();

        onLowPackets(numPackets);
        //Reevaluate numPackets because onLowPackets may add more packets.
        numPackets = (int)(outRel.size() + outUnrel.size());

        if (numPackets <= 0) {
          if (feederTimeout)
            outQCtrl.timedWait(feederTimeout);
          else
            outQCtrl.wait();
        }
      }
    }

    if (!shutdown) {
      //Check which queue woke us up.  Doing the check this way gives
      //absolute priority to reliable packets.
      bool reliable = !outRel.empty();
      assert(reliable || !outUnrel.empty());

      //Do throttled writes
      updateRates();
      if (outRemain > 0) {
        //Yes, this check will let us dip below 0, but overall we will make
        //up for it by waiting for it to go above 0 again.
        Buffer raw;
        prepareSend( ((reliable) ? outRel : outUnrel), raw);
        raw << PacketParser::END_OF_PACKET;
        outRemain -= raw.getPosition();

        //Release the mutex in case rawWrite blocks
        outQCtrl.release();
        if (owner.sockets.rawWrite(reliable, raw) != raw.getPosition()) {
          //We sleep here for a bit because we want to favor onExit if that is going to
          //happen.  Else this failure will occur.  Or we will favor a "real" error
          //more descriptive than a write error.
          Thread::sleep( 250 );
          owner.processError( LowLevelError(Error::Write) );
        }
        outQCtrl.acquire();
        
      } else {
        //Else we don't have any available bandwidth and we must wait!
        outQCtrl.release();
        Thread::sleep(TIME_STEP / 1000);
        outQCtrl.acquire();
      }
    }
  }
  outQCtrl.release();

  //We want to try to send the required ExitPacket, if possible, over the
  //reliable connection.
  //We need a good way to make sure this doesn't block though, but the
  //current solution here of assuming rawWrite won't block will have to do
  //for now.
  Buffer raw;
  ExitPacket temp;
  raw << temp << PacketParser::END_OF_PACKET;
  int ret = owner.sockets.rawWrite(true, raw);
  if (ret > raw.getPosition()) {
    gnedbgo1(4, "ExitPacket sent (%d).", ret);
  } else if ( ret > 0 ) {
    gnedbgo1(4, "ExitPackt not completely sent (%d).", ret);
  } else {
    gnedbgo1(4, "ExitPacket not sent (%d).", ret);
  }

  //Now that we have finished, release the PacketFeeder.
  LockCV lock( outQCtrl );
  feeder.reset();
  feederAllowed = false;
}

void PacketStream::addIncomingPacket(Packet* packet) {
  if (packet->getType() != RateAdjustPacket::ID) {
    inQCtrl.acquire();
    in.push(packet);
    inQCtrl.release();
  } else {
    //We want to "intercept" RateAdjustPackets
    outQCtrl.acquire();
    maxOutRate = ((RateAdjustPacket*)packet)->rate;
    gnedbgo1(2, "Received new outgoing rate limit of %d", maxOutRate);
    setupCurrRate();
    outQCtrl.release();
  }
}

void PacketStream::prepareSend(std::queue<Packet*>& q, Buffer& raw) {
  //outQCtrl must be acquired for this function.
  //While there are packets left and they won't overflow the Buffer
  while (!q.empty() &&
         raw.getPosition() + q.front()->getSize() <
         Buffer::RAW_PACKET_LEN - (int)sizeof(PacketParser::END_OF_PACKET)) {

    q.front()->writePacket(raw);
    delete q.front();
    q.pop();
  }
}

void PacketStream::setupCurrRate() {
  //Precalculate the current outgoing rate, keeping in mind that the value of
  //is the "largest" and means unlimited rate (or "unchecked").  Unlimited is
  //OK only if they are both at 0.  outQCtrl should be acquired when this
  //function is running.
  if (reqOutRate == 0)
    currOutRate = maxOutRate;
  else if (maxOutRate == 0)
    currOutRate = reqOutRate;
  else
    currOutRate = (reqOutRate < maxOutRate) ? reqOutRate : maxOutRate;

  //Discover the rate stepping.
  outRateStep = currOutRate / TIME_STEPS_PER_SEC;

  gnedbgo2(2, "  Negotiated current rate: %d, rate step: %d",
    currOutRate, outRateStep);
}

void PacketStream::updateRates() {
  //The out remain is part of the out queue, so outQCtrl must be locked when
  //we call this function.

  if (currOutRate > 0) {
    //Find the time difference in number of steps
    int timeDiff =
      (Timer::getCurrentTime() - lastTime).getTotaluSec() / TIME_STEP;
    
    outRemain += outRateStep * timeDiff;
    //Because of the math here, we compensate/take advatnage of integer
    //rounding.
    lastTime += TIME_STEP * timeDiff;
    //We won't allow large bursts of data -- no more than 1 second's worth.
    if (outRemain > currOutRate)
      outRemain = currOutRate;

  } else {
    //Else, we are not rate limiting, so we set outRemain to some fake value.
    outRemain = 1;
  }
}

void PacketStream::onLowPackets( int numPackets ) {
  if (feeder && numPackets <= lowPacketsThreshold) {
    gnedbgo(4, "onLowPackets event generated.");
    feeder->onLowPackets(*this);
  }
}

}
