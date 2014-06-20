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
#include "../include/gnelib/Client.h"
#include "../include/gnelib/ClientListener.h"
#include "../include/gnelib/ClientConnection.h"
#include "../include/gnelib/ConnectionParams.h"
#include "../include/gnelib/SyncConnection.h"
#include "../include/gnelib/Error.h"
#include "../include/gnelib/CustomPacket.h"
#include "../include/gnelib/RawPacket.h"

namespace GNE {
  
Client::Client() : listener(NULL) {
}

Client::sptr Client::create() {
  sptr ret( new Client() );
  ret->thisPtr = ret;
  return ret;
}

Client::~Client() {
}

bool Client::open(const Address& dest, const ConnectionParams& p, ClientListener* listener) {
  assert( listener != NULL );
  assert( dest );

  ConnectionParams cp( p );

  ourConn = ClientConnection::create();
  sptr temp = thisPtr.lock();
  assert( temp );
  cp.setListener( temp );
  this->listener = listener;

  assert( ourConn );
  return ourConn->open( dest, cp );
}

/**
 * \bug finish implementation.
 */
Error Client::connect( int ms ) {
  assert( ourConn );
  ourConn->connect();
  ourConn->join();
  if ( ourConn->isConnected() )
    return Error();
  else {
    LockMutex lock(sync);
    if ( connectError.getCode() == Error::NoError )
      return Error( Error::ConnectionTimeOut );
    else
      return connectError;
  }
}

bool Client::isConnected() {
  if ( !ourConn )
    return false;
  else
    return ourConn->isConnected();
}

PingInformation Client::getPingInfo() const {
  return pingInfo;
}

ClientConnection& Client::getConnection() {
  assert( ourConn );
  return *ourConn;
}

void Client::onConnect( SyncConnection& newConn ) {
  CustomPacket buf;

  //First, read from the server if there is a player slot open and we are
  //accepted.  If not, throw a connection refused error.
  gbool accepted;
  newConn >> buf;
  buf.getData() >> accepted;
  if (!accepted) {
    newConn.disconnect();
    throw Error(Error::ConnectionRefused);
  }
  assert( !accepted );
}

void Client::onConnectFailure(const Error& error) {
  LockMutex lock(sync);
  connectError = error;
}

void Client::onDisconnect() {
  listener->callOnDisconnect();
}

void Client::onExit() {
}

void Client::onTimeout() {
  listener->callOnTimeout();
}

void Client::onError( const Error& error ) {
}

void Client::onFailure( const Error& error ) {
}

void Client::onReceive() {
}

} //namespace GNE
