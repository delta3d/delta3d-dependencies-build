#ifndef _CLIENT_H_adsg352
#define _CLIENT_H_adsg352

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

#include "ConnectionListener.h"
#include "ClientConnection.h"
#include "PingPacket.h"
#include "Error.h"
#include "Mutex.h"

namespace GNE {
  class Address;
  class ConnectionParams;
  class ClientListener;
  class SyncConnection;

/**
 * @ingroup highlevel
 *
 * The center of the client-side high-level GNE API.  The Client class
 * maintains a connection to the server, and a list of other players on that
 * server (ClientPeer objects).
 */
class Client : private ConnectionListener {
public:
  typedef SmartPtr<Client> sptr;
  typedef WeakPtr<Client> wptr;

private: //ctor is private because of member thisPtr
  /**
   * Initializes this ClientConnection.  The listener is passed in the open
   * method.
   */
  Client();

public:
  /**
   * Creates a ClientConnection.  The listener is passed in the open method.
   */
  static sptr create();

  /**
   * Destructor.
   */
  virtual ~Client();

  /**
   * Opens the socket, ready for connect, but does not yet connect.  All of
   * the relvant parameters for establishing the connection are passed into
   * this function.  If there is already an error, the function returns true.
   * @param dest the destination address.
   * @param p the connection parameters.  The ConnectionListener object set
   * here is ignored.
   * @param listener the ClientListener to serve as the listener for this
   * Client.
   */
  bool open(const Address& dest, const ConnectionParams& p,
            ClientListener* listener);

  /**
   * Starts trying to connect to the server.  Waits for the given amount of
   * time for the connection to complete.  If the connection does not succeed,
   * returns an error.  If the connection succeeded, then the returned Error
   * has an error code of Error::NoError.  Note that the connect time also
   * includes the time for the onConnect handlers to complete.
   */
  Error connect( int ms );

  /**
   * Returns true if connected to the server.
   */
  bool isConnected();

  /**
   * Returns the most current ping information about the connection to the
   * server.  Note that the connection process includes discovering the ping
   * information.
   */
  PingInformation getPingInfo() const;

  /**
   * Returns the ClientConnection this object is using to communicate to the
   * server.  The Client must be connected to the server before using this
   * method.
   */
  ClientConnection& getConnection();

private:
  virtual void onConnect( SyncConnection& newConn );
  virtual void onConnectFailure(const Error& error);
  virtual void onDisconnect();
  virtual void onExit();
  virtual void onTimeout();
  virtual void onError( const Error& error );
  virtual void onFailure( const Error& error );
  virtual void onReceive();

private:
  wptr thisPtr;
  ClientConnection::sptr ourConn;
  ClientListener* listener;
  PingInformation pingInfo;

  Error connectError;

  Mutex sync;

  //Used so we can convert to ConnectionListener::sptr
  friend class boost::shared_ptr<ConnectionListener>;
};

} //namespace GNE

#endif

