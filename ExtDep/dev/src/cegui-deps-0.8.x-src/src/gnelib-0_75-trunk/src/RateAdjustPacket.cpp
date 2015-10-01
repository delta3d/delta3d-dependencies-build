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
#include <gnelib/RateAdjustPacket.h>
#include <gnelib/Packet.h>
#include <gnelib/Buffer.h>

namespace GNE {

const int RateAdjustPacket::ID = 3;

RateAdjustPacket::RateAdjustPacket() : Packet(ID), rate(0) {
}

RateAdjustPacket::~RateAdjustPacket() {
}

int RateAdjustPacket::getSize() const {
  return Packet::getSize() + Buffer::getSizeOf(rate);
}

void RateAdjustPacket::writePacket(Buffer& raw) const {
  Packet::writePacket(raw);
  raw << rate;
}

void RateAdjustPacket::readPacket(Buffer& raw) {
  Packet::readPacket(raw);
  raw >> rate;
}

}
