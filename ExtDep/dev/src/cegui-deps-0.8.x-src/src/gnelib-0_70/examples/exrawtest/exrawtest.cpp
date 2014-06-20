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
 * exrawtest -- Basically a test of the Buffer class.  Does show usage of the
 * Buffer class, but the usage in this case because this is a test uses the
 * class in "hackish" ways.
 *
 * This is called rawtest because it used to test an old class called
 * RawPacket (may it rest in peace), but now tests its superior child, Buffer,
 * which is much safer to use and guards against buffer under and overflows.
 */

#include <gnelib.h>
#include <iostream>
#include <cassert>

using namespace std;
using namespace GNE;
using namespace GNE::Console;

void endianTest() {
  gout << " * Now doing endian tests." << endl;
  //Note: This code has nothing to do with the proper usage of Buffer.
  //It is meant ONLY as a test to make sure Buffer is properly converting
  //the the right endian format, and to discover this system's endian format.
  int x = 15;
  gout << "This system is little-endian: " << (((char*)&x)[0] == 15) << endl;
  gout << "This system is big-endian: " << (((char*)&x)[3] == 15) << endl;

  //Now test to make sure Buffer converts from the system to little.
  Buffer endianTest;
  endianTest << x;
  endianTest.flip();
  gbyte t[4];

  //Read the integer we just wrote into a raw byte array.
  endianTest.readRaw(t, 4);
  gout << "Buffer must be in little-endian format." << endl;
  gout << "Buffer is in little-endian format: " << (t[0] == 15) << endl;
  gout << "Buffer is in big-endian format: " << (t[3] == 15) << endl;
  assert(t[0] == 15);
  gout << endl;
}

void multiTest() {
  gout << " * Now writing a Buffer..." << endl;

  //Create some binary and string data.
  gbyte block[16] = {'a', 'b', 'a', 'a', 'c', 'a', 'd', 'a', 'e', '1', 'a',
    'a', 'a', '4', 'a', 'a'};
  char nulls[10] = {'n', 'u', 'l', 'l', '\0', '\0', 't', 'e', 's', 't'};
  string nullsStr(nulls, 10);

  Buffer raw;
  raw << (gint32)56 << "superlala" << (guint8)124 << (gint16)26
      << (gsingle)12.5 << (gdouble)123.4 << nullsStr;
  raw.writeRaw(block, 16);
  
  int shouldBeSize = (sizeof(int) + 10 + sizeof(NLubyte) +
    sizeof(short) + sizeof(float) +
    sizeof(double) + nullsStr.size() + 1 + 16);

  gout << "Raw length: " << raw.getPosition() << endl;
  gout << " should be: " << shouldBeSize << endl;
  assert ( raw.getPosition() == shouldBeSize );

  raw.flip();
  assert ( raw.getPosition() == 0 );

  Buffer raw2( raw ); //make a copy, just to test.
  assert ( raw2.getPosition() == raw.getPosition() ||
           raw2.getCapacity() == raw.getCapacity() ||
           raw2.getLimit() == raw.getLimit() );

  gout << "Now reading from the same data..." << endl;

  //Create variables to read into that match those above.
  gint32 a;
  string b;
  guint8 c;
  gint16 d;
  gsingle e;
  gdouble f;
  string g;
  memset(block, 0, 16);

  //Read back.
  raw2 >> a >> b >> c >> d >> e >> f >> g;
  raw2.readRaw(block, 16);

  gout << a << endl << b << endl << (int)c << endl << d << endl
       << e << endl << f << endl;

  for (int count=0; count<16; count++) {
    gout << block[count] << ' ';
  }
  gout << endl;
  gout << "Data was of length: " << raw2.getPosition() << " (should be as above)" << endl;
  gout << "String1 length: " << b.length() << " (should be 9)" << endl;
  gout << "String2 length: " << g.length() << " (should be " << nullsStr.length() << ")" << endl;
}

void failTests() {
  gout << " * Now testing fail cases..." << endl;
  gout << " Tests passed: ";
  //Let's make Buffer fail!

  try {
    Buffer tooSmall( 0 );
    tooSmall << (guint32)15;
  } catch ( Error& e ) {
    assert ( e.getCode() == Error::BufferOverflow );
    gout << "1 ";
  }
  try {
    Buffer tooSmall( 1 );
    tooSmall << (guint32)15;
  } catch ( Error& e ) {
    assert ( e.getCode() == Error::BufferOverflow );
    gout << "2 ";
  }
  try {
    Buffer tooSmall( 2 );
    tooSmall << (guint32)15;
  } catch ( Error& e ) {
    assert ( e.getCode() == Error::BufferOverflow );
    gout << "3 ";
  }

  Buffer justRight( 4 );
  justRight << (guint32)15;
  gout << "4 ";

  justRight.flip();
  guint32 temp;
  justRight >> temp;
  gout << "5 ";

  try {
    justRight >> temp;
  } catch ( Error& e ) {
    assert ( e.getCode() == Error::BufferUnderflow );
    gout << "6 ";
  }

  Buffer limitTest;
  limitTest.setLimit( 0 );
  gout << "7a ";
  try {
    limitTest.setLimit( limitTest.getCapacity() + 1 );
  } catch ( Error& e ) {
    assert ( e.getCode() == Error::InvalidBufferLimit );
    gout << "7b ";
  }

  try {
    limitTest << "hello";
  } catch ( Error& e ) {
    assert ( e.getCode() == Error::BufferOverflow );
    gout << "8 ";
  }

  limitTest.clear();
  limitTest << "Hello";
  assert( limitTest.getPosition() == Buffer::getSizeOf( "Hello" ) );
  gout << "9a ";
  try {
    limitTest.setLimit( 3 );
  } catch ( Error& e ) {
    assert ( e.getCode() == Error::InvalidBufferLimit );
    gout << "9b ";
  }

  Buffer posTest( 15 );
  posTest.setPosition( 15 );
  try {
    posTest.setPosition( 16 );
  } catch ( Error& e ) {
    assert ( e.getCode() == Error::InvalidBufferPosition );
    gout << "10 ";
  }
}

int main(int argc, char* argv[]) {
  initGNE(NO_NET, atexit);
  initConsole();
  Console::setTitle("GNE Buffer Test");

  string during;
  try {
    during = "endianTest";
    endianTest();

    during = "multiTest";
    multiTest();

    during = "failTests";
    failTests();

  } catch ( Error& e ) {
    gout << "UNCAUGHT EXCEPTION: " << e << endl;
    gout << "  during: " << during << endl;

  } catch ( ... ) {
    gout << "UNCAUGHT EXCEPTION" << endl;
    gout << "  during: " << during << endl;
  }
  
  gout << "Press a key to continue: " << endl;
  getch();

  return 0;
}


