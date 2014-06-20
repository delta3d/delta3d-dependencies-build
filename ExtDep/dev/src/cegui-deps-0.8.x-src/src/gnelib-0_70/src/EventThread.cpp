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
#include "../include/gnelib/EventThread.h"
#include "../include/gnelib/ConnectionListener.h"
#include "../include/gnelib/Connection.h"
#include "../include/gnelib/Thread.h"
#include "../include/gnelib/Timer.h"
#include "../include/gnelib/Time.h"
#include "../include/gnelib/Error.h"
#include "../include/gnelib/ConditionVariable.h"
#include "../include/gnelib/Lock.h"

namespace GNE {

EventThread::EventThread( const Connection::sptr& conn )
: Thread("EventThr", Thread::HIGH_PRI), ourConn(conn),
onReceiveEvent(false), onTimeoutEvent(false),
onDisconnectEvent(false), onExitEvent(false), failure(NULL) {
  gnedbgo(5, "created");
  setType( CONNECTION );
}

EventThread::sptr EventThread::create( const Connection::sptr& conn ) {
  sptr ret( new EventThread( conn ) );
  ret->setThisPointer( ret );
  return ret;
}

EventThread::~EventThread() {
  //we shouldn't have to lock anything since only one thread should ever be here.

  while (!eventQueue.empty()) {
    delete eventQueue.front();
    eventQueue.pop();
  }

  delete failure;

  gnedbgo(5, "destroyed");
}

ConnectionListener::sptr EventThread::getListener() const {
  LockCV lock( listenSync );
  return eventListener;
}

void EventThread::setListener( const ConnectionListener::sptr& listener) {
  LockCV lock( listenSync );

  //Acquire eventSync because of the wait loop check
  LockCV lock2( eventSync );
  eventListener = listener;

  //Signal the event thread in case it is waiting for a listener.
  eventSync.signal();
}

int EventThread::getTimeout() const {
  return timeout.getTotalmSec();
}

void EventThread::setTimeout(int ms) {
  int microsec;
  if (ms > INT_MAX / 1000)
    microsec = INT_MAX / 1000;
  else
    microsec = ms * 1000;

  {
    LockMutex lock( timeSync );
    if (ms != 0) {
      timeout = Time(0, microsec);
      nextTimeout = Timer::getAbsoluteTime() + timeout;
    } else {
      nextTimeout = timeout = Time();
    }
  }

  //Wake up the event thread if it is sleeping, which is needed if there is
  //no timeout currently and the event thread is waiting forever on eventSync.
  eventSync.signal();
}

void EventThread::onDisconnect() {
  gnedbgo(1, "onDisconnect Event triggered.");
  //We acquire the mutex to avoid the possiblity of a deadlock between the
  // test for the shutdown variable and the wait.
  LockCV lock( eventSync );
  onDisconnectEvent = true;
  eventSync.signal();
}

void EventThread::onExit() {
  gnedbgo(1, "onExit Event triggered.");

  //Guarantee that either onExit or onFailure will be called, never both.
  LockCV lock( eventSync );
  if ( !failure && !onDisconnectEvent ) {
    onExitEvent = true;
    eventSync.signal();
  } else {
    gnedbgo(1, "onExit event ignored due to failure or disconnect.");
  }
}

void EventThread::onFailure(const Error& error) {
  gnedbgo1(1, "onFailure Event: %s", error.toString().c_str());

  //Guarantee that either onExit or onFailure will be called, never both.
  LockCV lock( eventSync );
  if ( !onExitEvent && !onDisconnectEvent ) {
    failure = new Error(error);
    eventSync.signal();
  } else {
    gnedbgo(1, "onFailure event ignored due to onExit or disconnect.");
  }
}

void EventThread::onError(const Error& error) {
  gnedbgo1(1, "onError Event: %s", error.toString().c_str());

  LockCV lock( eventSync );
  eventQueue.push(new Error(error));
  eventSync.signal();
}

void EventThread::onReceive() {
  gnedbgo(4, "onReceive event triggered.");

  //reset the timeout counter
  resetTimeout();

  LockCV lock( eventSync );
  onReceiveEvent = true;
  eventSync.signal();
}

void EventThread::shutDown() {
  //Yep.  No setting of shutdown.  We want to try to close gracefully.  If we
  //can't do that we couldn't respond to shutdown either.
  ourConn->disconnect();

  LockCV lock( eventSync );
  eventSync.signal();
}

void EventThread::run() {
  while ( true ) {
    //Yup.  No checking of shutdown.  When shutDown is called we call disconnect
    //on our connection, which should lead to a graceful shutdown.
    LockCVEx eventLock( eventSync );
    //Wait while we have no listener and/or we have no events.
    while (!eventListener || (!onReceiveEvent && !failure &&
           !onDisconnectEvent && eventQueue.empty() &&
           !onExitEvent && !onTimeoutEvent) ) {
      //Calculate the time to wait
      if ( timeout == Time() ) {
        //wait "forever"
        eventSync.wait();
      } else {
        //wait until a timeout would occur
        eventSync.timedWait(nextTimeout);
        checkForTimeout();
      }
    }
    eventLock.release();

    checkForTimeout();

    //To prevent deadlocks, we copy our listener, so that we don't need to hold
    //listenSync during the event.
    LockCVEx listenLock( listenSync );
    ConnectionListener::sptr listener = eventListener;
    listenLock.release();

    //Check for events, processing them if events are pending
    if (onExitEvent) {
      listener->onExit( *ourConn );
      ourConn->disconnect();
      onExitEvent = false; //set this after onDisconnectEvent is set
      //we want to reevaluate listener (because of SyncConnection), so we don't
      //directly call onDisconnect here.

    } else if (failure) {
      listener->onFailure( *ourConn, *failure );
      ourConn->disconnect();
      delete failure;
      failure = NULL; //set this after onDisconnectEvent is set

    } else if (onDisconnectEvent) {
      listener->onDisconnect( *ourConn );
      return;  //terminate this thread since there are no other events to
      //process -- onDisconnect HAS to be the last.

    } else if (onReceiveEvent) {
      //This is set to false before in case we get more packets during the
      //onReceive event.
      onReceiveEvent = false;
      listener->onReceive( *ourConn );

    } else if (onTimeoutEvent) {
      onTimeoutEvent = false;
      listener->onTimeout( *ourConn );

    } else {
      LockCVEx lock( eventSync );
      assert(!eventQueue.empty());
      Error* e = eventQueue.front();
      eventQueue.pop();
      lock.release();

      //When we get here this is the only reason left why we were woken up!
      listener->onError( *ourConn, *e );
      delete e;
    }
  }
}

void EventThread::checkForTimeout() {
  LockMutexEx lock( timeSync );

  if ( timeout == Time() )
    return;

  Time t = nextTimeout;
  lock.release();

  if ( Timer::getAbsoluteTime() > t )
    onTimeout();
}

void EventThread::resetTimeout() {
  LockMutex lock( timeSync );

  if ( timeout != Time() ) {
    nextTimeout = Timer::getAbsoluteTime() + timeout;
  }
}

void EventThread::onTimeout() {
  gnedbgo(4, "onTimeout event triggered.");

  //reset the timeout counter
  resetTimeout();

  LockCV lock( eventSync );
  onTimeoutEvent = true;
  eventSync.signal();
}

} //namespace GNE
