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
#include "../include/gnelib/Server.h"
#include "../include/gnelib/SyncConnection.h"
#include "../include/gnelib/CustomPacket.h"
#include "../include/gnelib/RawPacket.h"

namespace GNE {

/**
 * This is a class that the server side uses to refuse a client.
 */
class RefuseClient : public ConnectionListener {
public:
  void onNewConn(SyncConnection& conn2) {
    CustomPacket buf;
    //Tell the client that they have been refused
    buf.getData() << gFalse;
    conn2 << buf;
    conn2.disconnect();
    throw Error(Error::ConnectionRefused);
  }
private:
};

Server::Server( int players ) : maxPlayers(players),
joinsAllowed(false), currPlayerId(1) {
  if ( players < 1 || players > 255 )
    players = 1;
}

Server::~Server() {
}
  
bool Server::open( int port ) {
  return ServerConnectionListener::open( port );
}

bool Server::startServer() {
  assert( !isListening() );

  joinsAllowed = true;
  if (listen())
    return true;
  return false;
}

bool Server::isListening() const {
  return ServerConnectionListener::isListening();
}

Address Server::getLocalAddress() const {
  return ServerConnectionListener::getLocalAddress();
}

void Server::changePlayerLimit( int players ) {
  assert( players > 0 && players <= 255 );
  if (players > 0 && players <= 255 ) {
    maxPlayers = players;
  }
}

void Server::refuseJoins( bool refuse ) {
  joinsAllowed = false;
}

ServerPlayerList& Server::getConnectedPlayers() {
  return players;
}

int Server::numConnected() const {
  return players.numPlayers();
}

ChannelProvider& Server::getChannelProvider() {
  return chans;
}

void Server::onListenFailure(const Error& error, const Address& from,
                             ConnectionListener* listener) {
  delete listener;
}


void Server::onListenSuccess(ConnectionListener* listener) {
}

void Server::getNewConnectionParams(ConnectionParams& params) {
}

} //namespace GNE
