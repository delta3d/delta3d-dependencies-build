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

/**
 * exhello
 * Everyone knows the "Hello World" program.  Perhaps it's been coded
 * too many times.  However, the GNE coders just plain don't care ;).
 * This is an example to show the minimum code needed to connect and send
 * data, in this case, "Hello Server (or Client)!" to the other end of the
 * connection.  This program uses asyncronous event-driven methods.
 *
 * Well... perhaps not the minimum.  Lots of errors can happen over network
 * connections that we have to handle for this program to properly execute
 * when conditions aren't perfectly ideal, like when we can't reach the
 * server.
 *
 * The good part is that once you get over a lot of the overhead needed to
 * start a GNE program, that code can be used as a template for other GNE
 * programs -- and additionally -- using more features of GNE and doing
 * more will only require a little more code.
 */

#include <gnelib.h>
#include <iostream>
#include <string>

using namespace std;
using namespace GNE;
using namespace GNE::Console;
using namespace GNE::PacketParser;

#include "shared.h"

class OurClient : public ConnectionListener {
public: //typedefs
  typedef SmartPtr<OurClient> sptr;
  typedef SmartPtr<OurClient> wptr;

protected:
  OurClient() {
    mprintf("Client listener created.\n");
  }

public:
  static sptr create() {
    return sptr( new OurClient() );
  }

  ~OurClient() {
    mprintf("Client listener destroyed.\n");
  }

  void onDisconnect( Connection& conn ) { 
    mprintf("Client just disconnected.\n");
  }

  void onExit( Connection& conn ) {
    mprintf("Server gracefully disconnected.\n");
  }

  void onConnect(SyncConnection& conn2) {
    Connection& conn = *conn2.getConnection();
    mprintf("Connection to server successful.\n");
    mprintf("  From us at %s/TCP to server at %s/TCP.\n",
      conn.getLocalAddress(true).toString().c_str(),
      conn.getRemoteAddress(true).toString().c_str());
    //Test to see if we have an unreliable local address, and if so, report
    //what the addresses are.
    if (conn.getLocalAddress(false)) {
      mprintf("  From us at %s/UDP to server at %s/UDP.\n",
        conn.getLocalAddress(false).toString().c_str(),
        conn.getRemoteAddress(false).toString().c_str());
    } else {
      mprintf("  Unreliable connection refused by server.\n");
    }
  }

  void onReceive( Connection& conn ) {
    Packet* message = NULL;
    while ( (message = conn.stream().getNextPacket()) != NULL ) {
      if ( message->getType() == HelloPacket::ID ) {
        HelloPacket* helloMessage = (HelloPacket*)message;
        LockObject lock( gout );
        gout << "got message: \"" << helloMessage->getMessage() << '\"'
             << endl;
      } else
        mprintf("got bad packet.\n");
      destroyPacket( message );
    }
  }

  void onFailure( Connection& conn, const Error& error ) {
    mprintf("Socket failure: %s\n", error.toString().c_str());
    //No need to disconnect, this has already happened on a failure.
  }

  void onError( Connection& conn, const Error& error ) {
    mprintf("Socket error: %s\n", error.toString().c_str());
    conn.disconnect();//For simplicity we treat even normal errors as fatal.
  }

  void onConnectFailure( Connection& conn, const Error& error) {
    //Since we are using join in our client connecting code, this event is
    //not really needed, but we can display the error message here or in the
    //doClient function when it finds out the connection failed.  Either way
    //does the same thing.
    mprintf("Connection to server failed.\n");
    mprintf("GNE reported error: %s\n", error.toString().c_str());
  }
};

class OurServer : public ConnectionListener {
public: //typedefs
  typedef SmartPtr<OurServer> sptr;
  typedef SmartPtr<OurServer> wptr;

protected:
  OurServer() : received(false) {
    mprintf("Server listener created\n");
  }

public:
  static sptr create() {
    return sptr( new OurServer() );
  }

  virtual ~OurServer() {
    mprintf("Server listener killed\n");
  }

  void onDisconnect( Connection& conn ) { 
    //Call receivePackets one last time to make sure we got all data.
    //It is VERY possible for data still left unread if we get this event,
    //even though we read all data from onReceive.
    receivePackets( conn );
    mprintf("ServerConnection just disconnected.\n");
    if (!received)
      mprintf("No message received.\n");
  }

  void onExit( Connection& conn ) {
    mprintf("Client gracefully disconnected.\n");
  }

  void onNewConn( SyncConnection& conn2) {
    Connection& conn = *conn2.getConnection();
    mprintf("Connection received; waiting for message...\n");
    mprintf("  From us at %s/TCP to client at %s/TCP.\n",
      conn.getLocalAddress(true).toString().c_str(),
      conn.getRemoteAddress(true).toString().c_str());
    //Test to see if we have an unreliable local address, and if so, report
    //what the addresses are.
    if (conn.getLocalAddress(false)) {
      mprintf("  From us at %s/UDP to client at %s/UDP.\n",
        conn.getLocalAddress(false).toString().c_str(),
        conn.getRemoteAddress(false).toString().c_str());
    } else {
      mprintf("  Unreliable connection refused by client.\n");
    }
  }

  void onReceive( Connection& conn ) {
    receivePackets( conn );
  }

  void onFailure( Connection& conn, const Error& error ) {
    mprintf("Socket failure: %s\n", error.toString().c_str());
  }

  void onError( Connection& conn, const Error& error ) {
    mprintf("Socket error: %s\n", error.toString().c_str());
    conn.disconnect();
  }

  //Tries to receive and process packets.
  //This function responds to any requests.  Note that it is called in
  //onDisconnect and it is perfectly valid to send data from onDisconnect --
  //it just won't ever be sent ;), but there is no reason to pass in a param
  //and check for disconnection just so we don't send the data.
  void receivePackets( Connection& conn ) {
    //This time we use the SmartPtr version of getNextPacket, to show both
    //ways.  Using the SP version we don't need to call destroyPacket.
    Packet::sptr message;
    while ( (message = conn.stream().getNextPacketSp() ) ) {
      if ( message->getType() == HelloPacket::ID ) {
        HelloPacket::sptr helloMessage = static_pointer_cast<HelloPacket>( message );
        mprintf("got message: \"%s\"\n", helloMessage->getMessage().c_str());
        received = true;
        
        //Send Response
        mprintf("  Sending Response...\n");
        HelloPacket response("Hello, client!  I'm the event-driven server!");
        conn.stream().writePacket(response, true);
      } else
        mprintf("got bad packet.\n");
    }
  }

private:
  bool received;
};

void OurListener::getNewConnectionParams(ConnectionParams& params) {
  params.setInRate(iRate);
  params.setOutRate(oRate);
  //We want to also listen for hellos from unreliable channels.  Note that
  //exsynchello will NOT request unreliable, but that's OK -- if no
  //unreliable socket exists, unreliable data will be sent reliable.
  params.setUnrel(true);
  params.setListener( OurServer::create() );
}

int main(int argc, char* argv[]) {
  doMain("Event-Driven");
  return 0;
}

void doClient(int outRate, int inRate, int port) {
#ifdef _DEBUG
  initDebug(DLEVEL1 | DLEVEL2 | DLEVEL3 | DLEVEL4 | DLEVEL5, "client.log");
#endif
  string host;
  gout << "Enter hostname or IP address: ";
  gin >> host;

  Address address(host);
  address.setPort(port);
  if (!address)
    errorExit("Invalid address.");
  gout << "Connecting to: " << address << endl;

  //uncomment the loop and reduce sleep time to perform a stress test.
  //for (int i=0; i < 100; i++) {
    ConnectionParams params( OurClient::create() );
    params.setUnrel(true);
    params.setOutRate(outRate);
    params.setInRate(inRate);
    ClientConnection::sptr client = ClientConnection::create();
    if (client->open(address, params))
      errorExit("Cannot open client socket.");
    
    client->connect();
    client->waitForConnect();
    
    //Check if our connection was successful.
    if (client->isConnected()) {
      
      //Send our information
      HelloPacket message("Hello, server!  I'm the event-driven client!");
      client->stream().writePacket(message, true);
      
      //This sends another hello over the unreliable connection.  exsynchello
      //can't use unreliable connections because it uses SyncConnection, but
      //it chose to refuse an unreliable connection when we connected.  When
      //no unreliable connection exists, unreliable packets are sent reliably
      //so doing this will send it over UDP (or IPX) when connecting to an
      //exhello server, but over TCP (or SPX) when connecting to exsynchello.
      client->stream().writePacket(message, false);

      //Wait a little for any responses.
      gout << "Waiting a couple of seconds for any responses..." << endl;
      Thread::sleep(2000);
      client->disconnectSendAll();      
    }

    //client will be destroyed here as its sptr will go out of scope.
  //}
}


