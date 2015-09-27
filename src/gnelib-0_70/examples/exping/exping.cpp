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
 * exping -- Shows how to use the PingPacket API and how to create and
 * respond to PingPackets.  Also functions as a test of the PingPacket
 * class.
 */

#include <gnelib.h>
#include <iostream>
#include <cassert>

using namespace std;
using namespace GNE;
using namespace GNE::PacketParser;
using namespace GNE::Console;

const int TIMEOUT = 2000;

void errorExit(const char* error);
int getPort(const char* prompt);
void doServer(int outRate, int inRate, int port);
void doClient(int outRate, int inRate, int port);
void doLocalTest();

//The PingTest class works on both the client and the server side.
class PingTest : public ConnectionListener {
public:
  typedef SmartPtr<PingTest> sptr;
  typedef WeakPtr<PingTest> wptr;

protected:
  PingTest() {}

public:
  static sptr create() {
    return sptr( new PingTest() );
  }

  ~PingTest() {}

  void onDisconnect( Connection& conn ) {
    //Get any packets that are left and shut down.
    receivePackets( conn );
  }

  void onReceive( Connection& conn ) {
    receivePackets( conn );
  }

  void onTimeout( Connection& conn ) {
    LockObject lock( gout );
    //The timeout is called when nothing has been received for our specified
    //timeout, or since the last onTimeout event.
    gout << "A connection is active and no message received or timeout in "
         << "the last " << TIMEOUT << " ms." << endl;
  }

  void onFailure( Connection& conn, const Error& error ) {
    LockObject lock( gout );
    gout << "Socket failure: " << error << endl;
    //No need to disconnect, this has already happened on a failure.
  }

  void onError( Connection& conn, const Error& error ) {
    {
      LockObject lock( gout );
      gout << "Socket error: " << error << endl;
    }
    conn.disconnect();//For simplicity we treat even normal errors as fatal.
  }

  void onConnectFailure( Connection& conn, const Error& error ) {
    LockObject lock( gout );
    gout << "Connection to server failed.   " << endl;
    gout << "  GNE reported error: " << error << endl;
  }

  void receivePackets( Connection& conn ) {
    //We check for PingPackets.  Anything else we get is an error though.
    Packet* next = conn.stream().getNextPacket();

    while (next != NULL) {

      if (next->getType() == PingPacket::ID) {
        PingPacket* ping = (PingPacket*)next;

        if (ping->isRequest()) {
          ping->makeReply();
          conn.stream().writePacket(*ping, true);

        } else {
          PingInformation info = ((PingPacket*)next)->getPingInformation();
          LockObject lock( gout );
          gout << "Ping response: round-trip: " << info.pingTime
            << ", clock offset: " << info.clockOffset << endl;
        }

      } else {
        LockObject lock( gout );
        gout << "We got a packet type (" << next->getType() <<
          ") that we aren't expecting!" << endl;
      }

      delete next;
      next = conn.stream().getNextPacket();
    }
  }
};

class OurListener : public ServerConnectionListener {
public:
  typedef SmartPtr<OurListener> sptr;
  typedef WeakPtr<OurListener> wptr;

protected:
  OurListener() {
  }

public:
  static sptr create() {
    sptr ret( new OurListener() );
    ret->setThisPointer( ret );
    return ret;
  }

  virtual ~OurListener() {}

  void onListenFailure(const Error& error, const Address& from, const ConnectionListener::sptr& listener) {
    LockObject lock( gout );
    gout << "Connection error: " << error;
    gout << "  Error received from " << from;
  }

  void getNewConnectionParams(ConnectionParams& params) {
    params.setListener( PingTest::create() );
    params.setTimeout(TIMEOUT);
  }

private:
};

void errorExit(const char* error) {
  gout << "Error: " << error << endl;
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

int main() {
  if (initGNE(NL_IP, atexit)) {
    cout << "Unable to initialize GNE" << endl;
    exit(2);
  }

  setGameInformation("GNE exping", 1);

  if (initConsole()) {
    cout << "Unable to initialize GNE Console" << endl;
    exit(3);
  }
  setTitle("GNE PingPacket Example"); 

  gout << "GNE PingPacket Example for " << GNE::VER_STR << endl;
  gout << "Local address: " << getLocalAddress() << endl;
  gout << "Should we act as the server, or the client?" << endl;
  gout << "Type 1 for client, 2 for server, or 3 for a local test: ";
  int type;
  gin >> type;

  int port;
  if (type == 2) {
    setTitle("GNE Net Performance Tester -- Server");
    gout << "Reminder: ports <= 1024 on UNIX can only be used by the superuser." << endl;
    port = getPort("listen on");
    doServer(0, 0, port);

  } else if (type == 1) {
    setTitle("GNE Net Performance Tester -- Client");
    port = getPort("connect to");
    doClient(0, 0, port);

  } else {
    doLocalTest();
  }

  return 0;
}

void doServer(int outRate, int inRate, int port) {
#ifdef _DEBUG
  //Generate debugging logs to server.log if in debug mode.
  initDebug(DLEVEL1 | DLEVEL2 | DLEVEL3 | DLEVEL5, "server.log");
#endif
  OurListener::sptr server = OurListener::create();
  if (server->open(port))
    errorExit("Cannot open server socket.");
  if (server->listen())
    errorExit("Cannot listen on server socket.");

  {
    LockObject lock(gout);
    gout << "Server is listening on: " << server->getLocalAddress() << endl;
    gout << "Press a key to shutdown server." << endl;
  }
  getch();
  
  //optional operation -- server will also shutdown when GNE is shutdown
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

  //We allocate it on the heap because PingTest deletes this connection.
  ConnectionParams params( PingTest::create() );
  params.setOutRate(outRate);
  params.setInRate(inRate);
  params.setTimeout(TIMEOUT);
  ClientConnection::sptr client = ClientConnection::create();
  if (client->open(address, params))
    errorExit("Cannot open client socket.");

  client->connect();
  client->waitForConnect();

  if (client->isConnected()) {
    gout << "Press a key to stop the testing. " << endl;
    gout << "Press s to send a ping, u to send a ping over unreliable, and q to quit." << endl;

    int ch = 0;
    while (client->isConnected() && ch != (int)'q') {
      //while we block on getch we can't look for disconnects until a key is
      //pressed.  If we cared we could sleep-spin using kbhit...
      ch = getch();
      if (ch == (int)'s') {
        PingPacket req;
        client->stream().writePacket(req, true);
      } else if (ch == (int)'u') {
        PingPacket req;
        client->stream().writePacket(req, false);
      }
    }

    if ( !client->isConnected() ) {
      gout << "Server dropped us . . . Exiting." << endl;
      Thread::sleep( 1000 );
    }

  } else {
    gout << "An error occured while connecting.  Press a key." << endl;
    getch();
  }

  client->disconnectSendAll();
}

void doLocalTest() {
  //Just creating the PingPacket registers the request and measures the time
  //from this point until we get it back.
  gout << "Creating a PingPacket." << endl;
  PingPacket test;
  assert(PingPacket::reqsPending() == 1);

  //Then the other side normally would receive a packet.  No reason why we
  //can't reply to ourselves!
  test.makeReply();

  //Then when you get the reply back, you call getPing on it.  This looks up
  //the unique request ID and finds the time difference, THEN THE ID IS
  //REMOVED FROM THE TABLE.  This means getPing will only work once for each
  //ping!  If you try to call it again or on an invalid reply, it will return
  //a 0 ping time.
  gout << "The ping time is: " << test.getPingInformation().pingTime
    << " seconds. (should be VERY small)" << endl;
  assert(PingPacket::reqsPending() == 0);
  gout << "An invalid ping packet ping time (should be 0): "
    << test.getPingInformation().pingTime << endl;

  gout << "Creating 3 PingPackets which we will let be 'late'" << endl;
  PingPacket l1, l2, l3;
  l1.makeReply(); //Make l1 a reply... We will try to use it later...
  assert(PingPacket::reqsPending() == 3);

  gout << "Creating another PingPacket." << endl;
  PingPacket longTest;
  assert(PingPacket::reqsPending() == 4);
  gout << "Waiting 350 ms." << endl;
  Thread::sleep(350);
  longTest.makeReply(); //It really doesn't matter when we call makeReply.
  gout << "Ping time: " << longTest.getPingInformation().pingTime << endl;
  assert(PingPacket::reqsPending() == 3);

  gout << "Waiting another 200ms." << endl;
  Thread::sleep(200);
  gout << "Declaring requests older than 500ms as 'late'.  Found: "
    << PingPacket::recoverLostRequests(Time(0, 500000)) << '.' << endl;
  assert(PingPacket::reqsPending() == 0);
  gout << "Ping for one of those late, removed, requests (should be 0): "
    << l1.getPingInformation().pingTime << endl;

  gout << "Press a key to continue." << endl;
  getch();
}
