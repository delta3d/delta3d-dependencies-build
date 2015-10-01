#ifndef _WRAPPERPACKET_H_ADG234
#define _WRAPPERPACKET_H_ADG234

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

#include <gnelib/Packet.h>

namespace GNE {
  
/**
 * @ingroup midlevel
 *
 * WrapperPacket is a Packet that encapsulates another packet for the purposes
 * of adding information to that packet.  A WrapperPacket on its own has no
 * identity; it is meant only to be used as a base class for the real packet
 * types that perform this common functionality.
 */
class WrapperPacket : public Packet {
public: //typedefs
  typedef SmartPtr<WrapperPacket> sptr;
  typedef WeakPtr<WrapperPacket> wptr;

public:
  virtual ~WrapperPacket();

  /**
   * Returns the current size of this packet in bytes.
   */
  virtual int getSize() const;

  /**
   * Returns the encapsulated data in this WrapperPacket.  There may not
   * currently be an encapsulated Packet, so this method may return NULL.
   */
  const Packet* getData() const;

  /**
   * Returns the encapsulated data in this WrapperPacket.  There may not
   * currently be an encapsulated Packet, so this method may return NULL.
   */
  Packet* getData();

  /**
   * Replaces the given packet with the current packet as this WrapperPacket's
   * data.  The given packet is copied with the Packet::makeClone method, if
   * it is not NULL.
   */
  void setData( const Packet* packet );

  /**
   * Writes the packet to the given Buffer. 
   */
  virtual void writePacket(Buffer& raw) const;

  /**
   * Reads this packet from the given Buffer.
   */
  virtual void readPacket(Buffer& raw);

  /**
   * Copies the given WrapperPacket into this one.  Calls Packet::operator=(
   * const Packet& rhs ).
   */
  WrapperPacket& operator= ( const WrapperPacket& rhs );
  
protected:
  /**
   * Initializes a new WrapperPacket with the given Packet ID and no
   * encapsulated Packet.
   */
  WrapperPacket( int id );

  /**
   * Initializes a new WrapperPacket with the given Packet ID and encapsulated
   * Packet.  The encapsulated Packet may be NULL.
   */
  WrapperPacket( int id, const Packet* packet );

  /**
   * Initializes this WrapperPacket with the given WrapperPacket.
   */
  WrapperPacket( const WrapperPacket& o );

private:
  /**
   * The encapsulated Packet.
   */
  Packet* packet;
};

} //namespace GNE

#endif

