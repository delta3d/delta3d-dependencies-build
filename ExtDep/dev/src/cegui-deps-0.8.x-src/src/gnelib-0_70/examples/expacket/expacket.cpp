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
 * expacket -- Shows how to derive a new type of packet, and create the
 * proper parsing functions interacting with Buffer to allow GNE to use
 * your packet.
 * This example does NOT show how to use the packet over the network.
 * See exhello for that.
 * Note that like exrawtest, this uses Packets and RawPackets in
 * non-standard ways, so this is not the normal end-user way to use GNE.
 * This example is mainly just for testing purposes of GNE.
 * But if you want to use the PacketParser and Buffer API to do something
 * interesting and custom like say "sending" GNE packets to a save file to
 * save your game state, which is not very far-fetched as when clients
 * connect in network games they are loading a saved game state.
 */

#include <gnelib.h>
#include <iostream>
#include <cassert>

using namespace std;
using namespace GNE;
using namespace GNE::PacketParser;
using namespace GNE::Console;

#include "expacket.h"

int main(int argc, char* argv[]) {
  initGNE(NO_NET, atexit);
  initConsole();
  Console::setTitle("GNE Packet Test");
  defaultRegisterPacket<PersonPacket>();
  //we don't register UnknownPacket to try to trigger an error later so we
  //can test error handling of the parser.
  
  PersonPacket jason;
  jason.age = 20;
  jason.firstName = "Jason";
  jason.lastName = "Winnebeck";
  PersonPacket elias;
  elias.age = 255;
  elias.firstName = "Elias";
  elias.lastName = "Pschernig";

  packetTest(jason, elias);
  parseTest(jason, elias);

  gout << "Press a key to continue: " << endl;
  getch();

  return 0;
}

void packetTest(const PersonPacket& jason, const PersonPacket& elias) {
  gout << "Creating two PersonPackets" << endl;

  Buffer raw;
  jason.writePacket(raw);
  Packet* temp = elias.makeClone();
  temp->writePacket(raw);
  PacketParser::destroyPacket( temp );

  raw.flip();

  PersonPacket t1;
  PersonPacket t2;

  /*
   * Read back the packets.  Note that we have to read in the ids, because
   * normally packets aren't used this way.  Normally the packet parser in GNE
   * will real the ID, then create the packet.  The packet needs not to read
   * its own ID.
   */
  NLubyte dummy;
  raw >> dummy;
  t1.readPacket(raw);
  raw >> dummy;
  raw >> t2;

  //Maybe I should make a "toString" method for PersonPacket, or an operator <<?
  gout << t1.firstName << ' ' << t1.lastName << ", " << (int)t1.age
    << " years.  (size/type: " << t1.getSize() << '/' << t1.getType() << ')' << endl;
  gout << t2.firstName << ' ' << t2.lastName << ", " << (int)t2.age
    << " years.  (size/type: " << t2.getSize() << '/' << t2.getType() << ')' << endl;
}

void parseTest(const Packet& jason, const Packet& elias) {
  gout << "Starting packet tests.  If no \"Unexpected values\" are seen, everything worked." << endl;
  Packet packet1;
  MyUnknownPacket packet2;

  Buffer raw1;
  
  //All packets we intend on parsing must end with END_OF_PACKET.  In normal
  //GNE usage, the library will terminate packets properly on send.
  raw1 << packet1 << packet2 << jason << packet1 << elias << END_OF_PACKET;

  raw1.flip();

  Packet* next;
  try {
    next = parseNextPacket( raw1 );
    if (next == NULL || next->getType() != 0)
      gout << "(1)Unexpected values." << endl;
    PacketParser::destroyPacket( next );

  } catch ( Error& e ) {
    gout << "(1)Unexpected values: Exception thrown: " << e << endl;
  }

  //This one should fail as we did not register UnknownPacket.
  try {
    next = parseNextPacket(raw1);
    gout << "(2)Unexpected values: Exception must occur." << endl;

  } catch ( Error& ) {
  }

  raw1.rewind();
  //After we register, we should be able to completely read the Buffer.
  defaultRegisterPacket<MyUnknownPacket>();

  try {
    while( (next = parseNextPacket(raw1)) )
      PacketParser::destroyPacket( next );

  } catch ( Error& e ) {
    gout << "(3)Unexpected values: Exception thrown: " << e << endl;
  }
}


