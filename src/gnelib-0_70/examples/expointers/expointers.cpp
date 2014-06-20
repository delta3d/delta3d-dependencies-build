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

/* expointers example
 *
 * This is more of a test to make sure that the code compiles under all of the
 * supported compilers because of flaky support for class and class member
 * templates.
 *
 * However, you can see all of the possible combonations of operations that
 * you can perform on the smart pointers.
 */

#include <gnelib.h>

#include <iostream>
#include <vector>
#include <cassert>
#include <string>

using namespace std;

using GNE::Console::gout;

class Base {
public:
  int x;

  Base( int x ) : x(x) {
    gout << "Base ctor: " << x << endl;
  }

  virtual ~Base() {
    gout << "Base dtor: " << x << endl;
  }
};

class Derived : public Base {
public:
  Derived( int x ) : Base( x ) {
    gout << "Derived ctor: " << x << endl;
  }

  virtual ~Derived() {
    gout << "Derived dtor: " << x << endl;
  }

};

//Provide a CustomDeleter just for testing.  The nifty thing about the smart
//pointers is you can use your own memory allocation scheme, or you can do any
//operation in addition to or instead of "delete" when an object dies.
template<class T>
class CustomDeleter {
public:
  void operator()( T* t ) const {
    gout << "Custom deleter called!" << endl;
    delete t;
  }
};

typedef GNE::SmartPtr<Base> BasePtr;
typedef GNE::SmartPtr<Derived> DerivedPtr;

typedef GNE::WeakPtr<Base> BaseWeakPtr;
typedef GNE::WeakPtr<Derived> BaseDerivedPtr;

//Tests strong pointers
void testStrong();
void testWeak();

int main( int argc, char* argv[] ) {
  GNE::initGNE( GNE::NO_NET, atexit );
  GNE::Console::initConsole( atexit );
  GNE::Console::setTitle( "GNE Smart Pointers Example/Test" );

  testStrong();
  testWeak();

  return 0;
}

void testStrong() {
  //Tests with no objects
  BasePtr nPtr;
  assert( !nPtr );

  //Test assignments and other things on a single object.
  BasePtr bPtr( new Derived( 10 ) );
  assert( bPtr );

  BasePtr bPtr2( bPtr );
  assert( bPtr == bPtr2 );

  bPtr2 = bPtr;
  assert( bPtr2 == bPtr );

  GNE::swap( bPtr, bPtr2 );
  assert( bPtr2 == bPtr );

  DerivedPtr dPtr;
  dPtr = GNE::static_pointer_cast<Derived>( bPtr );

  gout << dPtr << "->x = " << dPtr->x << endl;

  DerivedPtr dPtr2( dPtr );
  assert( dPtr == dPtr2 );
  assert( !(dPtr != dPtr2) );
  assert( !(dPtr < dPtr2) );

  bPtr = dPtr = dPtr2;
  bPtr.reset();
  dPtr.reset();
  dPtr2.reset();
  bPtr2.reset();

  //Testing with multiple objects
  bPtr.reset( new Base( 15 ) );
  bPtr2.reset( new Base( 20 ) );
  gout << "bPtr = " << bPtr << "->x = " << bPtr->x << endl;
  gout << "bPtr2 = " << bPtr2 << "->x = " << bPtr2->x << endl;
  gout << "swapping" << endl;
  bPtr.swap( bPtr2 );
  gout << "bPtr = " << bPtr << "->x = " << bPtr->x << endl;
  gout << "bPtr2 = " << bPtr2 << "->x = " << bPtr2->x << endl;

  //Hidden functions that should be used for debugging purposes ONLY!
  assert( bPtr.use_count() == 1 );
  assert( bPtr.unique() );
  assert( bPtr2.use_count() == 1 );
  assert( bPtr2.unique() );

  //Test use of the CustomDeleter.  There's no reason why we need one here.
  GNE::SmartPtr<int> intPtr( new int, CustomDeleter<int>() );
  *intPtr = 5;
  gout << *intPtr << endl;

  //Superficial test placing objects in an STL container
  std::vector<BasePtr> bPtrs;
  bPtrs.push_back( bPtr );
  bPtrs.push_back( bPtr2 );

  assert( bPtrs[0].get() == bPtr.get() );
  assert( bPtr.use_count() > 1 );
  assert( !bPtr.unique() );

  gout << "Strong pointer tests completed.  You should see destructors after this." << endl;
  gout << "  Press any key to continue" << endl;
  GNE::Console::getch();
}

void testWeak() {
  gout << endl << "Weak pointer test begin:" << endl;
  BasePtr bPtr( new Base( 100 ) );
  BaseWeakPtr bwPtr( bPtr );

  //again use_count and expired are for debugging only!  These methods are
  //inheriently unsafe in real usage (definitely unsafe in multithreaded apps).
  assert( bPtr.use_count() == 1 );
  assert( !bwPtr.expired() );

  BasePtr bPtr2( bwPtr.lock() );
  assert( bPtr.use_count() == 2 );

  bPtr.reset();
  bPtr2.reset();

  assert( bPtr.use_count() == 0 );
  assert( bwPtr.expired() );

  bPtr = bwPtr.lock();
  assert( !bPtr );

  gout << "Weak pointer tests completed.  Press any key to continue." << endl;
  GNE::Console::getch();
}
