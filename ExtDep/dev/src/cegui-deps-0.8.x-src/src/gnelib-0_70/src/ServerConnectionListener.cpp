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

#include "gneintern.h"
#include <gnelib/ServerConnectionListener.h>
#include <gnelib/ConnectionEventGenerator.h>
#include <gnelib/ServerConnection.h>
#include <gnelib/ConnectionListener.h>
#include <gnelib/Connection.h>
#include <gnelib/ConnectionParams.h>
#include <gnelib/GNE.h>
#include <gnelib/Address.h>
#include <gnelib/Errors.h>
#include <gnelib/Lock.h>

namespace GNE {

typedef std::vector<ServerConnectionListener::sptr> SCLList;
typedef SCLList::iterator SCLListIter;

static SCLList listeners;
static Mutex listSync;

ServerConnectionListener::ServerConnectionListener()
: listening(false), socket( NL_INVALID ) {
  gnedbgo(5, "created");
}

ServerConnectionListener::~ServerConnectionListener() {
  //We shouldn't be listening
  assert( !listening );

  //However... open could have been called but never listen.
  //This could cause a problem if called after GNE shutdown.
  rawClose();

  gnedbgo(5, "destroyed");
}

void ServerConnectionListener::closeAllListeners() {
  LockMutex lock( listSync );

  SCLListIter iter = listeners.begin();
  for ( ; iter != listeners.end(); ++iter )
    (*iter)->rawClose();

  listeners.clear();
}

bool ServerConnectionListener::open(int port) {
  LockMutex lock(sync);

  if ( socket == NL_INVALID ) {
    socket = nlOpen( (NLushort)port, NL_RELIABLE_PACKETS );
    return (socket == NL_INVALID);
  } else
    return false;
}

void ServerConnectionListener::close() {
  //must lock listSync before sync always.
  LockMutex lock( listSync );
  LockMutex lock2( sync );

  SCLList& l = listeners;
  l.erase( std::remove( l.begin(), l.end(), this_.lock() ), l.end() );

  rawClose();
}

bool ServerConnectionListener::listen() {
  //must lock listSync before sync always, so we are FORCED to do a defensive
  //lock on listSync.
  LockMutex lock( listSync );
  LockMutex lock2( sync );

  if ( socket == NL_INVALID )
    return true;

  NLboolean ret = nlListen(socket);
  if (ret == NL_TRUE) {
    gnedbgo1(3, "Registering listen socket %i", socket);

    //Lock our strong pointer, making sure setThisPointer was called.
    sptr this_strong = this_.lock();
    assert( this_strong );

    //Do the actual register.
    GNE::eGen->reg(socket, ServerListener::sptr( new ServerListener( this_strong ) ) );
    listening = true;

    //We shouldn't already be in this list...
    assert( std::find( listeners.begin(), listeners.end(), this_strong ) == listeners.end() );

    //Add us to the list.
    listeners.push_back( this_strong );

    //success
    return false;
  }

  return true;
}

bool ServerConnectionListener::isListening() const {
  LockMutex lock(sync);

  return listening;
}

void ServerConnectionListener::onReceive() {
  LockMutex lock(sync);

  NLsocket sock = nlAcceptConnection(socket);
  if (sock != NL_INVALID) {
    ConnectionParams params;
    getNewConnectionParams(params);

    if (!params) {
      //If the params were valid
      assert( !this_.expired() );
      ServerConnection::sptr newConn = ServerConnection::create(params, sock, this_.lock());
      gnedbgo2(4, "Spawning a new ServerConnection %x on socket %i",
        newConn.get(), sock);
      newConn->start();
    } else {
      //If the params are not valid, report the error
      onListenFailure( Error(Error::OtherGNELevelError), Address(),
        params.getListener());
    }
  } else {
    LowLevelError err = LowLevelError();
    gnedbgo1(1, "Listening failure (accept failed): %s",
      err.toString().c_str());
    onListenFailure( err, Address(), ConnectionListener::sptr() );
  }
}

Address ServerConnectionListener::getLocalAddress() const {
  LockMutex lock(sync);

  if (socket != NL_INVALID) {
    NLaddress ret;
    nlGetLocalAddr(socket, &ret);
    return Address(ret);
  } else {
    return Address();
  }
}

void ServerConnectionListener::setThisPointer( const sptr& thisPointer ) {
  this_ = thisPointer;
}

void ServerConnectionListener::rawClose() {
  LockMutex lock(sync);

  if (listening) {
    gnedbgo1(3, "Unregistering listen socket %i", socket);
    GNE::eGen->unreg(socket);
    listening = false;
  }
  
  if ( socket != NL_INVALID ) {
    nlClose(socket);
    socket = NL_INVALID;
  }
}

void ServerConnectionListener::processOnListenFailure( const Error& error, const Address& from, const ConnectionListener::sptr& listener) {
  onListenFailure( error, from, listener );
}

void ServerConnectionListener::processOnListenSuccess( const ConnectionListener::sptr& listener ) {
  onListenSuccess( listener );
}

void ServerConnectionListener::onListenSuccess(const ConnectionListener::sptr&) {
  //The default behavior for this event is to do nothing.
}

ServerConnectionListener::ServerListener::ServerListener(const ServerConnectionListener::sptr& listener)
: conn(listener) {
}

ServerConnectionListener::ServerListener::~ServerListener() {
}

void ServerConnectionListener::ServerListener::onReceive() {
  conn->onReceive();
}

}
