#ifndef EMPTYPACKET_H_MOK987
#define EMPTYPACKET_H_MOK987

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

#include <gnelib/SmartPtr.h>
#include <gnelib/WeakPtr.h>
#include <gnelib/Packet.h>

namespace GNE {

/**
 * The EmptyPacket is a packet that has no information.  This packet type is a
 * replacement for when Packet with a default constructor was used.  Normally
 * sending blank packets are not useful; however, there are a few purposes for
 * them, such as a "keep alive" packet to keep a connection alive.  If you are
 * wanting to use a blank packet for some purpose such as a end-of-data marker
 * or sending some message that requires no data, it is suggested that you
 * simply derive a class from Packet that adds no data, but has a unique ID so
 * it can be "recognized" easier.
 */
class EmptyPacket : public Packet {
public: //typedefs
  typedef SmartPtr<EmptyPacket> sptr;
  typedef WeakPtr<EmptyPacket> wptr;

public:
  /**
   * Constructs an EmptyPacket.
   */
  EmptyPacket();

  /**
   * The ID for this type of packet.
   */
  static const int ID;
};
}

#endif //EMPTYPACKET_H_MOK987
