#ifndef _SERVER_H_
#define _SERVER_H_

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

#include "PlayerList.h"
#include "ServerConnectionListener.h"
#include "ConditionVariable.h"
#include "ChannelProvider.h"

namespace GNE {

/**
 * @ingroup highlevel
 *
 * The basis of the server-side of the high-level GNE API.  This class extends
 * the GNE mid-level API class ServerConnectionListener, and replaces all of
 * its functionality.
 *
 * A server has a maximum number of players it will accept.  If the number of
 * connecting players plus connected players is equal to the maximum number
 * of players, all new connections are refused, until the number of players
 * drop.
 *
 * The server can also be configured to stop accepting new connections,
 * regardless of the number of players, with an optional reason (for example if
 * a game has started, and it does not allow joins during play).
 *
 * The server maintains a list of connecting and connected players.  The server
 * also maintains channels that players can join (or more correctly "be placed
 * into"), and act as a internal broadcast network, just like a chat room.  The
 * channels were originally designed to be chat channels, but were modified so
 * that any packet can be sent to a channel through a wrapping ChannelPacket
 * for maximum flexibility.  The most common use will be sending ChatPacket
 * packets through the channel.
 *
 * The Server class also provides convenience methods for managing the players,
 * and managing their transistions to different game states (which likely
 * require time synchronization).
 */
class Server : private ServerConnectionListener {
public:
  /**
   * Initalizes this class.
   * @param players the maximum number of players to accept.  Must be a number
   *                from 1 to 255, inclusive.  If this value is out of range,
   *                it will default to 1.
   */
  explicit Server( int players );

  /**
   * Destructor.
   */
  virtual ~Server();
  
  /**
   * Opens the Server ready for listening, but not yet listening.
   * @param port the port to listen on.
   * @return true if could not open a socket on the port.
   */
  bool open( int port );

  /**
   * Starts the server, meaning that it will begin to listen for new
   * connections up to the maximum number of players specified.
   * 
   * The method open must have been called before this one.
   * 
   * @return true if an error was immedately detected.
   */
  bool startServer();

  /**
   * Returns true if this Serve is active and listening for new connections.
   */
  bool isListening() const;

  /**
   * Returns the address of the listening socket.  The Server must be opened
   * when this function is called, but does not have to be listening.
   */
  Address getLocalAddress() const;    

  /**
   * Changes the maximum player limit for this server.  This will only apply
   * to new connections, and not to currently connecting or connected players.
   * You must boot or kick players yourself if you wish to reduce the number of
   * players on the server -- the Server object will only reject new
   * connections when the server is full.
   *
   * The numbers of players must be between 1 and 255, inclusive, because only
   * a single byte is used for player IDs.  If you want to set the maximum
   * number of players to 0, you should call the refuseJoins method.  If the
   * players parameter is out of range, the method has no effect.
   */
  void changePlayerLimit( int players );

  /**
   * Enables or disables the ability for new players to join, irregardless of
   * the maximum number of players set.  Use this method to temporarily
   * prevent players from joining the server (or permanently if you never turn
   * it back on).
   * @param refuse true to refuse joins, false to allow joins.
   */
  void refuseJoins( bool refuse );

  /**
   * Returns a ServerPlayerList consisting of all currently connected and
   * active players.  A ServerPlayer can become disconnected at any time.
   */
  ServerPlayerList& getConnectedPlayers();

  /**
   * Returns the number of currently connected players.  Note that this number
   * can change at any time as players join and disconnect.
   */
  int numConnected() const;

  /**
   * Returns the ChannelProvider for this Server, which you can use to send
   * packets to certain channels.
   */
  ChannelProvider& getChannelProvider();

protected:


private: //private methods
  /**
   * The default ctor, copy ctor, and operator= are invalid.
   */
  Server();
  Server( Server& );
  Server& operator=( Server& rhs ); 

private:
  virtual void onListenFailure(const Error& error, const Address& from,
                               ConnectionListener* listener);

  virtual void onListenSuccess(ConnectionListener* listener);

  virtual void getNewConnectionParams(ConnectionParams& params);
  
private: //Data members
  ChannelProvider chans;
  ServerPlayerList connecting;
  ServerPlayerList players;

  ConditionVariable monitor;

  int maxPlayers;
  bool joinsAllowed;

  int currPlayerId;
};

}

#endif

