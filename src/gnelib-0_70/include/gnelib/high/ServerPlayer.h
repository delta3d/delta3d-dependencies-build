#ifndef _SERVERPLAYER_H_jkh234
#define _SERVERPLAYER_H_jkh234

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
#include "PingPacket.h"
#include "Mutex.h"
#include "Player.h"
#include <boost/shared_ptr.hpp>

namespace GNE {
  class SyncConnection;
  class Error;
  class ServerPlayerListener;
  class ServerConnection;
  class Server;
  class PlayerData;

/**
 * @ingroup highlevel
 *
 * This class serves as the interface between the mid-level GNE API and the
 * high-level API.  This class will never need to be instantiated by the
 * library user, as this class is created and mainly used by the Server class.
 * It also acts as a bridge between ConnectionListener events and the higher
 * level ServerPlayerListener events.
 *
 * You will be interacting with instances of this class.  In the high level
 * API, this class replaces the functionality that was previously served by
 * ServerConnection.
 */
class ServerPlayer : public Player, private ConnectionListener {
public:
  /**
   * GNE uses reference counted pointers to the ServerPlayer objects, because
   * when you get a ServerPlayer pointer, when it disconnects, we have to know
   * when we can destroy the ServerPlayer object.
   *
   * GNE will always give you these smart pointers to ServerPlayer.  When you
   * are through using the smart pointer, you can let it be destructed by
   * going out of scope, or you can set it to NULL to drop the reference
   * immediately.  You can use the -> operator as usual to access the
   * ServerPlayer object as usual.
   */
  typedef boost::shared_ptr<ServerPlayer> pointer;

  /**
   * A weak pointer is a pointer to an object that does not affect when it is
   * destroyed.  The weak pointer will become null when the object is
   * destroyed.  If you need to keep the object around use pointer.
   */
  typedef boost::weak_ptr<ServerPlayer> weak_pointer;
  
public:
  /**
   * Constructs a new ServerPlayer with a new unique ID, its Server object,
   * and the PlayerData object representing its playerData.
   */
  ServerPlayer( Server& server, PlayerData& playerData, int id );

  virtual ~ServerPlayer();

  /**
   * Returns the PlayerData attached to this object.  The PlayerData is valid
   * for as long as the ServerPlayer object exists.
   */
  PlayerData& getPlayerData();

  /**
   * Returns the ServerConnection object for this ServerPlayer.
   */
  ServerConnection& getConnection();

  /**
   * Returns the Server object managing this player.
   */
  Server& getServer();

private:
  virtual void onNewConn( SyncConnection& newConn );
  virtual void onDisconnect();
  virtual void onExit();
  virtual void onTimeout();
  virtual void onError( const Error& error );
  virtual void onFailure( const Error& error );
  virtual void onReceive();
  
private:
  void handlePacket( const Packet& packet, int packetType );
  
private:
  //ServerPlayer is not copyable
  ServerPlayer( const ServerPlayer& o );
  ServerPlayer& operator= ( const ServerPlayer& rhs );
  
private:
  Server& server;
  ServerPlayerListener* listener;
  ServerConnection* ourConn;

  PlayerData* playerData;
};


} //namespace GNE

#endif

