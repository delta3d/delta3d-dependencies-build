#ifndef _ServerPlayerListener_H_
#define _ServerPlayerListener_H_

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

#include "ServerPlayer.h"

namespace GNE {
  class Server;
  
/**
 * @ingroup highlevel
 *
 * A ServerPlayerListener is a listener to a single ServerPlayer object.
 */
class ServerPlayerListener : public HighLevelListener {
public:
  ServerPlayerListener();

  virtual ~ServerPlayerListener();

  /**
   * Works just like its ConnectionListener::onNewConn counterpart, except
   * that at this time, the ServerPlayer object has been set up with ping
   * information and an ID, bandwidth has been negotiated, etc.
   */
  void onNewPlayer( SyncConnection& newConn );

protected:
  /**
   * Returns the Server object belonging to our ServerPlayer.
   */
  Server* getServer();

  /**
   * Returns the ServerPlayer we are listening to.
   */
  ServerPlayer::pointer getPlayer();
  
private:
  /**
   * Points to the ServerPlayer generating events for this listener.
   * The myServer and myPlayer variables are set before events are called on
   * this listener, and exist for convenience only, and they should not be
   * changed.
   */
  ServerPlayer::weak_pointer myPlayer;

private:
  /**
   * Sets the player currently sending events to this listener.
   */
  void setPlayer( Server* server, ServerPlayer* player );
  friend class ServerPlayer; //so it can call setPlayer
};

} //namespace GNE

#endif

