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

/**
 * exbroker
 * Test of ObjectBrokerServer and ObjectBrokerClient classes.  Not much of an
 * example because this usage is far from the practical usage, but it does
 * show and track the state of the ObjectBrokers while they interact.
 */

#include <gnelib.h>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

using namespace GNE;
using namespace GNE::PacketParser;
using namespace GNE::Console;

#include "PositionedText.h"

bool genericHandler( const Packet& packet, ObjectBrokerClient& obc,
                     TextConsole& out );
void successTest( const Packet& packet, ObjectBrokerClient& obc,
                  TextConsole& out );
void failTest( const Packet& packet, ObjectBrokerClient& obc,
               TextConsole& out );

ObjectCreationPacket::sptr
doSerializationTest( const ObjectCreationPacket::sptr& p );

void registerObjects();
void registerPackets();

int main(int argc, char* argv[]) {
  if (initGNE(NL_IP, atexit)) {
    exit(1);
  }
  initConsole();
  setTitle("GNE ObjectBrokers Test/Example");
  registerPackets();

  PositionedText t( "I'm a PositionedText!", 5, 23 );

  ObjectBrokerServer obs;
  ObjectBrokerClient obc;

  //Set up a text console, since PositionedText will be moving the cursor
  //around, using gout normally will not provide the desired results.
  int width, height;
  Console::mgetConsoleSize( &width, &height );
  TextConsole out(0, 0, width, 20 );

  //GNE is now using smart pointers for certain things.  This decision was made
  //with the high-level API because of a high difficulty tracking when objects
  //should be destroyed.  You can treat p like a pointer, and it will handle
  //when the packet should be destroyed (specifically when the pointer and any
  //of its copies go out of scope).
  ObjectCreationPacket::sptr p = obs.getCreationPacket( t );
  //This is strictly for testing, it writes the ObjectCreationPacket to a
  //Buffer, reads back a new one, and returns a new packet.
  p = doSerializationTest( p );

  assert( obc.numObjects() == 0 );
  assert( obc.getObjectById( t.getObjectId() ) == NULL );
  assert( obs.numObjects() == 1 );
  assert( obs.getObjectById( t.getObjectId() ) == &t );

  //We create the update packet before we use the previous packet, so we can
  //test for errors later.
  t.setText( "Updated message." );
  bool updateText = true;
  ObjectUpdatePacket::sptr updatePacket =
    obs.getUpdatePacket( t, (void*)&updateText );

  t.setPos( 20, 22 );
  updateText = false;
  ObjectUpdatePacket::sptr updatePacket2 =
    obs.getUpdatePacket( t, (void*)&updateText );

  out << "Giving creation packet BEFORE registering that object type." << endl;
  out << "This should generate an error message:" << endl;
  failTest( *p, obc, out );

  registerObjects();

  out << "Giving update packet BEFORE creating the object.  This should ";
  out << "generate an error message: " << endl;
  failTest( *updatePacket, obc, out );

  //Let's try it again.
  out << "You should see a message below if test succeeded, which includes ";
  out << "the object ID at the start.  Press a key to continue." << endl;
  successTest( *p, obc, out );
  //After this test succeeds, a completely new object separate from t exists,
  //created as a result of the packet.  Because of the way genericHandler is
  //written, we don't need to worry about keeping a pointer.
  assert( obc.numObjects() == 1 );
  assert( obc.getObjectById( t.getObjectId() ) != NULL );
  assert( obc.getObjectById( t.getObjectId() ) != &t );
  assert( obs.numObjects() == 1 );

  getch();

  //If we do it again, we should get a different error now.
  out << "Giving creation packet a second time.  You should see an error:" << endl;
  failTest( *p, obc, out );

  out << "Giving update packet" << endl;
  successTest( *updatePacket, obc, out );
  getch();

  out << "Now updating position of object with a different update packet." << endl;
  successTest( *updatePacket2, obc, out );
  getch();

  out << "Now we will create a death packet from the object and process it, ";
  out << "which will destroy the object created earlier." << endl;
  ObjectDeathPacket::sptr deathPacket = obs.getDeathPacket( t );
  obs.deregisterObject( t );
  assert( obc.numObjects() == 1 );
  assert( obs.numObjects() == 0 );
  successTest( *deathPacket, obc, out );

  getch();

  assert( obc.numObjects() == 0 );
  assert( obc.getObjectById( t.getObjectId() ) == NULL );
  assert( obs.numObjects() == 0 );
  assert( obs.getObjectById( t.getObjectId() ) == NULL );

  return 0;
}

bool genericHandler( const Packet& packet, ObjectBrokerClient& obc,
                     TextConsole& out ) {
  try {
    PositionedText& obj = (PositionedText&)( obc.usePacket( packet ) );

    if ( obj.isDead() )
      delete &obj;
    else if ( !obj.isDrawn() )
      obj.draw();

    return false;

  } catch ( const Error& e ) {
    out << e.toString() << endl;
    return true;
  }
}

void successTest( const Packet& packet, ObjectBrokerClient& obc,
                  TextConsole& out ) {
  if ( genericHandler( packet, obc, out ) )
    out << "***** TEST FAILED! *****" << endl;
  else
    out << "--Test Success." << endl;
}

void failTest( const Packet& packet, ObjectBrokerClient& obc,
               TextConsole& out ) {
  if ( genericHandler( packet, obc, out ) )
    out << "--Test Success." << endl;
  else
    out << "***** TEST FAILED! *****" << endl;
}

ObjectCreationPacket::sptr
doSerializationTest( const ObjectCreationPacket::sptr& p ) {
  Buffer raw;

  p->writePacket( raw );
  raw << PacketParser::END_OF_PACKET;

  raw.flip();
  try {
    Packet* newPacket = PacketParser::parseNextPacket( raw );
    assert( newPacket != NULL );

    return ObjectCreationPacket::sptr( (ObjectCreationPacket*) newPacket );

  } catch ( ... ) {
    assert( false );
    return ObjectCreationPacket::sptr();
  }
}

void registerObjects() {
  ObjectBrokerClient::registerObject( PositionedTextPacket::ID,
    PositionedText::createFromPacket );
}

void registerPackets() {
  defaultRegisterPacket< PositionedTextPacket               >();
  defaultRegisterPacket< PositionedTextPositionUpdatePacket >();
  defaultRegisterPacket< PositionedTextTextUpdatePacket     >();
}
