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
#include <gnelib/Packet.h>
#include <gnelib/PacketParser.h>
#include <gnelib/Buffer.h>

namespace GNE {

Packet::Packet(int id) : type((guint8)id) {
}

Packet::Packet( const Packet& o ) : type(o.type) {
}

Packet::~Packet() {
}

Packet* Packet::makeClone() const {
  return PacketParser::clonePacket( this );
}

int Packet::getType() const {
  return (int)type;
}

int Packet::getSize() const {
  return Buffer::getSizeOf(type);
}

void Packet::writePacket(Buffer& raw) const {
  raw << type;
}

void Packet::readPacket(Buffer& raw) {
  //don't read type here, because our parser does this.
}

Packet& Packet::operator = (const Packet& rhs) {
  //The type should already be the same
  assert(type == rhs.type);
  return *this;
}

}
