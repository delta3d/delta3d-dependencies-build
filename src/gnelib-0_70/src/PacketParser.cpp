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

#include "../include/gnelib/gneintern.h"
#include "../include/gnelib/PacketParser.h"
#include "../include/gnelib/Buffer.h"
#include "../include/gnelib/Mutex.h"
#include "../include/gnelib/Lock.h"
#include "../include/gnelib/Error.h"
#include "../include/gnelib/Errors.h"

//Packet type includes used for registration.
#include "../include/gnelib/Packet.h"
#include "../include/gnelib/CustomPacket.h"
#include "../include/gnelib/ExitPacket.h"
#include "../include/gnelib/PingPacket.h"
#include "../include/gnelib/RateAdjustPacket.h"
#include "../include/gnelib/ObjectCreationPacket.h"
#include "../include/gnelib/ObjectUpdatePacket.h"
#include "../include/gnelib/ObjectDeathPacket.h"
#include "../include/gnelib/ChannelPacket.h"

namespace GNE {
namespace PacketParser {

static Mutex mapSync;

struct PacketFuncs {
  PacketCreateFunc  createFunc;
  PacketCloneFunc   cloneFunc;
  PacketDestroyFunc destroyFunc;
};

//Originally this was a map, but this array is only 3k, and its faster and
// easier to use a static array in this case.
static PacketFuncs packets[256];

/**
 * \todo GNE authors -- don't forget to add additional packets to this
 *       function as GNE expands.
 */
//This is a function defined only in GNE.cpp, as this is an internal init
// function.  The additions are hardcoded so registerPacket can do the proper
// asserts for the user's packets.  This function must also be called to
// properly init the parser.
void registerGNEPackets() {
  for (int c=0; c<256; c++) {
    packets[c].createFunc = NULL;
    packets[c].cloneFunc = NULL;
    packets[c].destroyFunc = NULL;
  }

  defaultRegisterPacket<Packet>();
  defaultRegisterPacket<CustomPacket>();
  defaultRegisterPacket<ExitPacket>();
  defaultRegisterPacket<RateAdjustPacket>();
  registerPacket( PingPacket::ID, PingPacket::create, defaultPacketCloneFunc<PingPacket>, defaultPacketDestroyFunc<PingPacket> );
  defaultRegisterPacket<ChannelPacket>();
  defaultRegisterPacket<ObjectCreationPacket>();
  defaultRegisterPacket<ObjectUpdatePacket>();
  defaultRegisterPacket<ObjectDeathPacket>();
  /*
  packets[0] = Packet::create;
  packets[1] = CustomPacket::create;
  packets[2] = ExitPacket::create;
  packets[3] = RateAdjustPacket::create;
  packets[4] = PingPacket::create;
  packets[5] = ChannelPacket::create;
  packets[6] = ObjectCreationPacket::create;
  packets[7] = ObjectUpdatePacket::create;
  packets[8] = ObjectDeathPacket::create;
  */
}

void registerPacket( guint8 id,
                     PacketCreateFunc createFunc,
                     PacketCloneFunc cloneFunc,
                     PacketDestroyFunc destroyFunc ) {
  LockMutex lock( mapSync );

  assert(packets[id].createFunc  == NULL);
  assert(packets[id].cloneFunc   == NULL);
  assert(packets[id].destroyFunc == NULL);

  packets[id].createFunc  = createFunc;
  packets[id].cloneFunc   = cloneFunc;
  packets[id].destroyFunc = destroyFunc;

  assert(packets[id].createFunc  != NULL);
  assert(packets[id].cloneFunc   != NULL);
  assert(packets[id].destroyFunc != NULL);
}

Packet* createPacket( guint8 id ) {
  mapSync.acquire();
  PacketCreateFunc func = packets[id].createFunc;
  mapSync.release();

  assert( func );
  if ( func )
    return func();
  else
    return NULL;
}

Packet* clonePacket( const Packet* p ) {
  guint8 id = (guint8)p->getType();

  mapSync.acquire();
  PacketCloneFunc func = packets[id].cloneFunc;
  mapSync.release();

  assert( func );
  if ( func )
    return func( p );
  else
    return NULL;
}

void destroyPacket( Packet* p ) {
  //if statement, because destroyPacket( NULL ) is OK.
  if ( p ) {
    guint8 id = (guint8)p->getType();

    mapSync.acquire();
    PacketDestroyFunc func = packets[id].destroyFunc;
    mapSync.release();

    assert( func );
    if ( func )
      func( p );
  }
}

Packet* parseNextPacket( Buffer& raw ) {
  //Read next packet ID
  guint8 nextId;
  raw >> nextId;

  //Check for end of packet, returning if it is the end.
  if (nextId == END_OF_PACKET)
    return NULL;

  //Check for packet registration, parsing if it is registered.
  mapSync.acquire();
  PacketCreateFunc func = packets[nextId].createFunc;
  mapSync.release();

  //This section is split off to keep the above critial section small as
  //many threads will be using this function.
  if (!func) {
    gnedbg1(1, "Unknown packet type %i received.", (int)nextId);
    throw UnknownPacket( (int)nextId );
  }

  Packet* ret = func();
  try {
    ret->readPacket(raw);
  } catch( Error& ) {
    destroyPacket( ret );
    throw;
  } catch( ... ) {
    destroyPacket( ret );
    assert( "readPacket must throw subclasses of Error!" != 0 );
    return NULL;
  }
  return ret;

}

} //namespace PacketParser
} //namespace GNE
