#ifndef _CLIENTPEER_H_145512
#define _CLIENTPEER_H_145512

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

#include "Player.h"
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace GNE {
class Client;

/**
 * @ingroup highlevel
 *
 */
class ClientPeer : public Player {
public:
  /**
   * GNE uses reference counted pointers to the ClientPeer objects, because
   * when you get a ClientPeer pointer, when it disconnects, we have to know
   * when we can destroy the ClientPeer object.
   *
   * GNE will always give you these smart pointers to ClientPeer.  When you
   * are through using the smart pointer, you can let it be destructed by
   * going out of scope, or you can set it to NULL to drop the reference
   * immediately.  You can use the -> operator as usual to access the
   * ClientPeer object as usual.
   */
  typedef boost::shared_ptr<ClientPeer> pointer;

  /**
   * A weak pointer is a pointer to an object that does not affect when it is
   * destroyed.  The weak pointer will become null when the object is
   * destroyed.  If you need to keep the object around use pointer.
   */
  typedef boost::weak_ptr<ClientPeer> weak_pointer;

public:
  ClientPeer( Client* client, int id );

  virtual ~ClientPeer();
};

} //namespace GNE

#endif

