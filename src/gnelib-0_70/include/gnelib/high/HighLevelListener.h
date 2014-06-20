#ifndef _HIGHLEVELLISTENER_H_
#define _HIGHLEVELLISTENER_H_

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

#include "Mutex.h"

namespace GNE {
  class Error;
  class SyncConnection;
  class Packet;
  class Time;
  
/**
 * @ingroup highlevel
 *
 * The HighLevelListener serves as the abstract base class for the
 * ServerPlayerListener and ClientListener classes.  Some of the events in
 * this class are based off the GNE mid-level API class, ConnectionListener,
 * so most concepts from that class apply to this one.
 *
 * The call* functions work just like their like-named functions, but provide
 * synchronization so that only one event is ever active at a time for a given
 * listener.  This should simplify user code complexity just as it did for
 * ConnectionListener.  User code should never need to call these functions or
 * use the "sync" Mutex object, unless you wanted to create additional custom
 * events in your listener, you may want to create proxy methods similar to
 * the public methods of this class.
 */
class HighLevelListener {
public:
  virtual ~HighLevelListener();

  /**
   * Proxy for like-named protected function, and provides Synchronization.
   * See main class description.  You should not need to ever call this method.
   */
  void callOnDisconnect();

  /**
   * Proxy for like-named protected function, and provides Synchronization.
   * See main class description.  You should not need to ever call this method.
   */
  void callOnTimeout();

  /**
   * Proxy for like-named protected function, and provides Synchronization.
   * See main class description.  You should not need to ever call this method.
   */
  void callOnServerQuit( const Time& quitTime );

  /**
   * Proxy for like-named protected function, and provides Synchronization.
   * See main class description.  You should not need to ever call this method.
   */
  void callOnError( const Error& error );

  /**
   * Proxy for like-named protected function, and provides Synchronization.
   * See main class description.  You should not need to ever call this method.
   */
  void callOnFailure( const Error& error );

  /**
   * Proxy for like-named protected function, and provides Synchronization.
   * See main class description.  You should not need to ever call this method.
   */
  void callOnReceive( int channel, const Packet& packet, int type );

protected:
  /**
   * Works just like its ConnectionListener::onDisconnect counterpart.  This
   * event is likely to be the last event received, but it will not be the
   * last time this object will be seen.
   */
  virtual void onDisconnect();
  
  /**
   * Works just like its ConnectionListener::onTimeout counterpart.
   */
  virtual void onTimeout();

  /**
   * Event received when the server announces that it will be shutting down
   * soon.  Gives the clients a chance to do things before the server quits.
   * Returns the time the server said it would finally boot all clients, based
   * on its own time.
   */
  virtual void onServerQuit( const Time& quitTime );

  /**
   * This event works just like its ConnectionListener::onError counterpart.
   */
  virtual void onError( const Error& error );

  /**
   * This event works just like its ConnectionListener::onFailure counterpart.
   */
  virtual void onFailure( const Error& error );

  /**
   * Event triggered when a packet is received.  This is different from
   * ConnectionListener::onReceive that this event is called every time a
   * packet comes in, and you must process this packet (or you could place it
   * into a queue if you must keep it).  GNE handles issues with reading
   * multiple packets and handling memory.  The reason the method is different
   * from mid-level GNE is that the high-level API intercepts many kinds of
   * packets and processes them specially before you receive them, thus you
   * should not read packets directly from the Connection object's queue.
   *
   * @param channel the channel, a shortcut for packet.getChannel()
   * @param packet the packet of data
   * @param type the packet's type, a shortcut for packet.getType()
   */
  virtual void onReceive( int channel, const Packet& packet, int type );
  
protected:
  //abstract base class
  HighLevelListener();

  /**
   * Sync mutex used by GNE to protect the events.  User code should not need
   * to touch this.
   */
  Mutex sync;

};

} //namespace GNE

#endif

