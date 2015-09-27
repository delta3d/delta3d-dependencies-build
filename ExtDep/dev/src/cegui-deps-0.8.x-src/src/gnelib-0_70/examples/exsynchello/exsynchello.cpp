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
 * exsynchello
 * This is the same thing as exhello, but using only SyncConnections.
 */

#include <gnelib.h>
#include <iostream>
#include <string>

using namespace std;
using namespace GNE;
using namespace GNE::Console;
using namespace GNE::PacketParser;

#include "../exhello/shared.h"

class OurServer : public ConnectionListener {
  typedef SmartPtr<OurServer> sptr;
  typedef WeakPtr<OurServer> wptr;

protected:
  OurServer() : received(false) {
    //Remember that LockObject locks the passed object in ctor, and releases it
    //in dtor.  It's safer than acquire/release but is a new addition to the
    //API so you will still see the old acquire/release code about.
    LockObject lock( gout );
    gout << "Server instance created" << endl;
  }

public:
  static sptr create() { 
    return sptr( new OurServer() );
  }

  virtual ~OurServer() {
    LockObject lock( gout );
    gout << "ServerConnection instance killed" << endl;
  }

  void onDisconnect( Connection& conn ) { 
    LockObject lock( gout );
    gout << "ServerConnection just disconnected." << endl;
    if (!received)
      gout << "  No message received." << endl;
  }

  void onNewConn(SyncConnection& conn) {
    gout << acquire << "Connection received from "
         << conn.getConnection()->getRemoteAddress(true)
         << "; waiting for messages..." << endl << release;

    try {
      //We loop this twice because we will be getting two requests, because
      //exhello sends two packets to test reliable and unreliable testing,
      //but since we refused unreliable connections in OurListener, we will
      //get it reliably and on the SyncConnection.
      for (int c=0; c<2; ++c) {
        HelloPacket message;
        conn >> message;
        received = true;
        gout << acquire << "Got message: \"" << message.getMessage() << "\""
          << endl << release;
        
        HelloPacket response("Hello, client!  I'm the syncronous server!");
        conn << response;
      }
    } catch (Error& e) {
      LockObject lock( gout );
      gout << "An error occured during communications." << endl;
      gout << "  The error was: " << e << endl;
      throw;
    }
  }

private:
  bool received;
};

void OurListener::getNewConnectionParams(ConnectionParams& params) {
  params.setInRate(iRate);
  params.setOutRate(oRate);
  //We are only using sync connections, so we don't need the unreliable
  //socket.  If anyone wants to send unreliable data to us, it will come
  //through the reliable channel instead, so this is OK even though
  //exhello will try to request an unreliable connection.
  params.setUnrel(false);
  params.setListener( OurServer::create() );
}

int main(int argc, char* argv[]) {
  doMain("Syncronous");
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

  //Uncomment the loop for a stress test.
  //for (int i=0; i<100; ++i) {
    ClientConnection::sptr clientConn = ClientConnection::create();
    SyncConnection::sptr syncConn = SyncConnection::create( clientConn );

    //Reference variable used for convience so we can use operators << and >>
    SyncConnection& client = *syncConn;

    try {
      //Since only one client can exist, acquire and release is not needed on
      //gout.
      gout << "Opening client socket." << endl;
      ConnectionParams p( ConnectionListener::getNullListener() );
      p.setUnrel(false);
      client.open(address, p);
      gout << "Attempting to connect." << endl;
      client.connect();
      
      gout << "Connection completed, sending messages to server." << endl;
      HelloPacket message("Hello, server!  I'm the syncronous client!");
      client << message;
      client << message;
      
      gout << "Waiting for messages back from server." << endl;
      client >> message;
      gout << "Received \"" << message.getMessage() << "\" from the server." << endl;
      client >> message;
      gout << "Received \"" << message.getMessage() << "\" from the server." << endl;
      
      gout << "Disconnecting." << endl;
      client.disconnect();

    } catch (Error& e) {
      gout << "An error occured while trying to communicate." << endl;
      gout << "  The error was: " << e << endl;
    }
  //}
}
