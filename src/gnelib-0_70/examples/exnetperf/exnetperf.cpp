/* GNE - Game Networking Engine, a portable multithreaded networking library.
 * Copyright (C) 2001-2006 Jason Winnebeck
 * Project website: http://www.gillius.org/gne/
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

/**
 * exnetperf -- Shows how to use the statistical functions in GNE.  This
 * example should serve well for GNE to measure network performance, as best
 * as is possible with the GNE and HawkNL APIs.  This example uses event-
 * driven networking since that is what is most likely to be used once the
 * game has started, and the method that most likely has the largest impact
 * on performace.  (SyncConnection will most likely be used only while
 * connecting).
 * This example could also be used to test the bandwidth throttling.
 * Right now this example isn't completed yet, but it is getting close.
 */

#include <gnelib.h>
#include "rndalgor.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include "StatsDisplay.h" //Our helper class for displaying the stats.

using namespace std;
using namespace GNE;
using namespace GNE::PacketParser;
using namespace GNE::Console;

void errorExit(const char* error);
int getPort(const char* prompt);
void getRates(int& iRate, int& oRate);
void doServer(int outRate, int inRate, int port);
void doClient(int outRate, int inRate, int port);

/**
 * A small wrapper around rndalgor from the jrnd library, which is not
 * thread-safe.
 */
class Randomizer {
public:
  Randomizer() {
    slongrand(time(NULL));
  }

  ~Randomizer() {}

  int getNum() {
    LockMutex lock( sync );
    return longrand();
  }

private:
  Mutex sync;
};

static StatsDisplay::sptr sDisplay;
static Randomizer rng;

//The PerfTester class works on both the client and the server side.
class PerfTester : public ConnectionListener, public PacketFeeder {
public:
  typedef SmartPtr<PerfTester> sptr;
  typedef WeakPtr<PerfTester> wptr;

  PerfTester() : packetsIn(0), packetsOut(0) {}
public:
  static sptr create() {
    return sptr( new PerfTester() );
  }

  ~PerfTester() {}

  void onDisconnect( Connection& conn ) {
    sDisplay->delConn(ourConn);
  }

  void onConnect(SyncConnection& conn) {
    ourConn = conn.getConnection();
    sDisplay->addConn(ourConn, &packetsIn, &packetsOut);
  }

  void onNewConn(SyncConnection& conn) {
    ourConn = conn.getConnection();
    sDisplay->addConn(ourConn, &packetsIn, &packetsOut);
  }

  void onReceive( Connection& conn ) {
    //We don't need to do anything to the data we are being sent.  The low-
    //level routines will keep track of the stats for us, so we just delete
    //the packets we get.
    Packet* next = conn.stream().getNextPacket();
    while (next != NULL) {
      delete next;
      packetsIn++;
      next = conn.stream().getNextPacket();
    }
  }

  void onFailure( Connection& conn, const Error& error ) {
    mlprintf(0, 0, "Socket failure: %s   ", error.toString().c_str());
    //No need to disconnect, this has already happened on a failure.
  }

  void onError( Connection& conn, const Error& error ) {
    mlprintf(0, 0, "Socket error: %s   ", error.toString().c_str());
    conn.disconnect();//For simplicity we treat even normal errors as fatal.
  }

  void onConnectFailure( Connection& conn, const Error& error ) {
    mprintf("Connection to server failed.   ");
    mprintf("  GNE reported error: %s   ", error.toString().c_str());
  }

  //The implementation of the only PacketFeeder interface method
  void onLowPackets( PacketStream& ps ) {
    //  Note that while only one event from a connection through its
    //ConnectionListener will be processed at a time, the PacketFeeder does
    //not follow this rule, so any of the events plus onLowPackets may be
    //running at the same time from different threads.
    //  The feeder will be called after the connection starts since there are
    //no packets to send yet.

    //We don't need to use ps because we store the connection pointer.
    writePackets( ps );
  }

  //Try to send out some more packets of random size with random databytes.
  void writePackets( PacketStream& ps ) {
    //Find packetsize in 32-bit words
    //We pick a range of 2 to 100 because that is the typical GNE packet
    //size in game.  GNE is meant to combine the packets to optimize
    //bandwith.
    //int packetSize = rng.getNum() % 48 + 2;

    //Big packet test, to represent GNE transmitting files or initial game
    //information.
    int packetSize = CustomPacket::getMaxUserDataSize() / 4 - 1;

    //Create a packet with random data
    CustomPacket temp;
    for (int c = 0; c < packetSize; c++)
      temp.getBuffer() << rng.getNum();

    ps.writePacket(temp, true);
    packetsOut++;
  }

private:
  int packetsIn;
  int packetsOut;
  Connection::sptr ourConn;
};

class OurListener : public ServerConnectionListener {
public:
  typedef SmartPtr<OurListener> sptr;
  typedef WeakPtr<OurListener> wptr;

protected:
  OurListener(int iRate, int oRate)
    : ServerConnectionListener(), iRate(iRate), oRate(oRate) {
  }

public:
  static sptr create( int iRate, int oRate ) {
    sptr ret( new OurListener( iRate, oRate ) );
    ret->setThisPointer( ret );
    return ret;
  }

  virtual ~OurListener() {}

  void onListenFailure(const Error& error, const Address& from, const ConnectionListener::sptr& listener) {
    mlprintf(0, 0, "Connection error: %s   ", error.toString().c_str());
    mlprintf(0, 1, "  Error received from %s   ", from.toString().c_str());
  }

  void getNewConnectionParams(ConnectionParams& params) {
    params.setRates(oRate, iRate);

    PerfTester::sptr tester = PerfTester::create();
    params.setListener(tester);
    params.setFeeder(tester);
  }

private:
  int iRate;
  int oRate;
};

void errorExit(const char* error) {
  shutdownConsole();
  cout << "Error: " << error << endl;
  exit(1);
}

int getPort(const char* prompt) {
  int port;
  gout << "Which port should we " << prompt << ": ";
  gin >> port;
  while ((port < 1) || (port > 65535)) {
    gout << "Ports range from 1 to 65535, please select one in this range: ";
    gin >> port;
  }
  return port;
}

void getRates(int& iRate, int& oRate) {
  gout << "GNE provides bandwith limits.  Enter 0 for no limit, or a value in bytes/sec"
    << endl;
  int dummy, oldy;
  mgetPos(&dummy, &oldy);
  gout << "Enter max out rate: ";
  gin >> oRate;
  gout << moveTo(40, oldy) << "max in rate: ";
  gin >> iRate;
}

int main() {
  if (initGNE(NL_IP, atexit)) {
    cout << "Unable to initialize GNE" << endl;
    exit(2);
  }
  enableStats();     //By default, stats are disabled.  This turns stat
                     //collection on.

  //Set our user version and "game" name both of which are used during the
  //connection process to verify our identity.
  setGameInformation("Net Perf Example", 1);

  if (initConsole()) {
    cout << "Unable to initialize GNE Console" << endl;
    exit(3);
  }
  setTitle("GNE Net Performance Tester");
  sDisplay = StatsDisplay::create(500);

  gout << "GNE Net Performance Tester for " << GNE::VER_STR << endl;
  gout << "Local address: " << getLocalAddress() << endl;
  gout << "Should we act as the server, or the client?" << endl;
  gout << "Type 1 for client, 2 for server: ";
  int type;
  gin >> type;

  int port;
  int iRate, oRate;
  if (type != 1) {
    setTitle("GNE Net Performance Tester -- Server");
    gout << "Reminder: ports <= 1024 on UNIX can only be used by the superuser." << endl;
    port = getPort("listen on");
    getRates(iRate, oRate);
    doServer(oRate, iRate, port);
  } else {
    setTitle("GNE Net Performance Tester -- Client");
    port = getPort("connect to");
    getRates(iRate, oRate);
    doClient(oRate, iRate, port);
  }

  return 0;
}

void doServer(int outRate, int inRate, int port) {
#ifdef _DEBUG
  //Generate debugging logs to server.log if in debug mode.
  initDebug(DLEVEL1 | DLEVEL2 | DLEVEL3 | DLEVEL5, "server.log");
#endif
  OurListener::sptr server = OurListener::create(inRate, outRate);
  if (server->open(port))
    errorExit("Cannot open server socket.");
  if (server->listen())
    errorExit("Cannot listen on server socket.");

  gout << "Server is listening on: " << server->getLocalAddress() << endl;
  gout << "Press a key to shutdown server." << endl;
  sDisplay->startDisplay();
  getch();

  //This is mostly optional.
  server->close();
}

void doClient(int outRate, int inRate, int port) {
#ifdef _DEBUG
  initDebug(DLEVEL1 | DLEVEL2 | DLEVEL3 | DLEVEL5, "client.log");
#endif
  string host;
  gout << "Enter hostname or IP address: ";
  gin >> host;

  Address address(host);
  address.setPort(port);
  if (!address)
    errorExit("Invalid address.");
  gout << "Connecting to: " << address << endl;
  gout << "Press a key except r to stop the testing.  Press r to change rates." << endl;

  PerfTester::sptr tester = PerfTester::create();
  ConnectionParams params( tester );
  params.setRates(outRate, inRate);
  params.setFeeder( tester );

  ClientConnection::sptr client = ClientConnection::create();
  if (client->open(address, params))
    errorExit("Cannot open client socket.");

  client->connect();
  client->waitForConnect();

  if (client->isConnected()) {
    
    sDisplay->startDisplay();
    //We allow the client to change the incoming and outgoing datarate on the
    //fly by pressing r.
    while (getch() == (int)'r') {
      char newRateStr[16] = "";
      int newRate = 3200;
      char clr[] = 
        "                                                                    ";
      //We can't use gin here because gin is not thread safe like gout is, this
      //is because the cursor moving around constantly.
      mlprintf(0, 21,
        "Pick a new requested outgoing rate (0 == no limit, -1 == no change):",
        client->stream().getRemoteOutLimit());
      lgetString(0, 22, newRateStr, 10);
      sscanf(newRateStr, "%d", &newRate);
      client->stream().setRates(newRate, -1);
      
      mlprintf(0, 23,
        "Pick a new maximum incoming rate (0 == no limit, -1 == no change):",
        client->stream().getRemoteOutLimit());
      lgetString(0, 24, newRateStr, 10);
      sscanf(newRateStr, "%d", &newRate);
      client->stream().setRates(-1, newRate);
      
      //Now we clear these lines so the user doesn't think they are still
      //inputting data.
      mlprintf(0, 21, clr);
      mlprintf(0, 22, clr);
      mlprintf(0, 23, clr);
      mlprintf(0, 24, clr);
    }
    
    //Turn off the PacketFeeder so when we disconnect we won't wait forever.
    client->stream().setFeeder( PacketFeeder::sptr() );
    client->disconnectSendAll();
  
  } else {
    gout << "An error occured while connecting.  Press a key." << endl;
    getch();
  }
}
