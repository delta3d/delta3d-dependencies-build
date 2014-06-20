#ifndef _PLAYERLIST_H_ABCD1234
#define _PLAYERLIST_H_ABCD1234

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
#include "ClientPeer.h"
#include "Mutex.h"
#include <boost/shared_ptr.hpp>
#include <vector>

namespace GNE {
  
/**
 * @ingroup highlevel
 *
 * A convenience class for storing a list of pointers to Player objects, and
 * contains algorithms to search for and locate players in that list, and to
 * perform operations on all of the players in the list.  This class is a
 * template, which takes subclasses of Player objects, for convienence so that
 * you do not have to cast parameters to the methods or their returns (which
 * may be impossible given the reference counted pointer implementation).
 *
 * There are two versions of this PlayerList then, one is ClientPeerList
 * that holds ClientPeer objects, and ServerPlayerList that holds ServerPlayer
 * objects
 *
 * PlayerList also provides for synchronization on the list.  At the current
 * time, only one thread may have the list "open" at one time.  "Open" is
 * defined as performing a global list operation through one of the methods,
 * or having an active iterator on the PlayerList.
 *
 * In the future, the API for list iteration may change, so that multiple
 * threads can be reading from the list if no threads are changing the list.
 */
template <class PlayerType>
class PlayerList {
public:
  typedef std::vector< PlayerType::pointer >::iterator iterator;
  typedef std::vector< PlayerType::pointer >::iterator const_iterator;

public:
  /**
   * Constructs a new, empty list.
   */
  PlayerList();

  virtual ~PlayerList();

  /**
   * Returns the current number of players in this list.
   */
  int numPlayers() const;

  /**
   * Given the ID, returns a Player object from the list whose ID is the
   * given ID, or NULL if no such player exists.
   */
  PlayerType::pointer getByID( int id ) const;

  /**
   * Adds a Player to the list.  This method will block until the list
   * becomes available (all open iterators are closed).
   */
  void addPlayer( PlayerType::pointer player );

  /**
   * Removes a Player from the list.  If the given player is not in the
   * list, the request is ignored.  This method will block until the list
   * becomes available (all open iterators are closed).
   */
  void removePlayer( PlayerType::pointer player );

  /**
   * Opens the list for reading, returning an iterator over the list, which
   * has the operations "*" and "++" (pre and post) defined.  You may not
   * assume that any other operations are valid on the iterator.
   *
   * This call opens the list, and no other threads may modify the list (they
   * however, CAN modify the Player objects themselves that appear in
   * the list).
   *
   * Note: in this initial implemenation only one thread can have the list
   * opened at a time, even if they are both for reading.  This restraint may
   * be lifted later when the more complicated code to handle this is written.
   */
  const_iterator* openListForReading();

  /**
   * Closes the list that was opened by "openListForReading".  Until this
   * method is called, other threads may be waiting on other operations.  You
   * must pass the iterator that was given to you by openListForReading.
   */
  void endReading( const_iterator* iter );

  /**
   * A convinence method, which iterates over the list, and writes a packet to
   * all of the members of this list.  Optionally can exclude a player (useful
   * for sending packets to everyone but the originator).
   *
   * @param packet the packet to send to everyone.
   * @param exclude an optional player to exclude from the sending.  Can be
   * NULL so that noone is excluded.
   */
  void sendToAll( const Packet& packet, const PlayerType::pointer exclude ) const;

private:
  //PlayerList is not copyable
  PlayerList( const PlayerList& o );
  PlayerList& operator=( PlayerList& rhs );

private:
  typedef std::vector< PlayerType::pointer > PlayerListT;

  mutable Mutex sync;

  PlayerListT players;

  const_iterator openedIter;
};

typedef PlayerList<ServerPlayer> ServerPlayerList;
//typedef PlayerList<ClientPeer> ClientPeerList;

} //namespace GNE

#endif

