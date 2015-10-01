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
#include <gnelib/ObjectCreationPacket.h>
#include <gnelib/Buffer.h>

namespace GNE {

const int ObjectCreationPacket::ID = 6;

ObjectCreationPacket::ObjectCreationPacket() : ObjectBrokerPacket( ID ) {
}

ObjectCreationPacket::ObjectCreationPacket( int objectId, const Packet& data )
: ObjectBrokerPacket( ID, objectId, &data ) {
}

ObjectCreationPacket::~ObjectCreationPacket() {
}
  
} //namespace GNE
