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
 * exconsole
 * shows off the new ConsoleBuffer/TextConsole classes, and acts also as a
 * partial test.
 */

#include <gnelib.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace GNE;
using namespace GNE::Console;

class ConsoleTest : public Thread {
public:
  typedef SmartPtr<ConsoleTest> sptr;
  typedef WeakPtr<ConsoleTest> wptr;

protected:
  ConsoleTest( ConsoleBuffer& cb ) : cb(cb) {
  }

public:
  static sptr create( ConsoleBuffer& cb ) {
    sptr ret( new ConsoleTest( cb ) );
    ret->setThisPointer( ret );
    return ret;
  }

  void run() {
    cb << acquire << "This line should not ";
    sleep( 1000 );
    cb << "be broken up." << endl << release;
  }

private:
  ConsoleBuffer& cb;
};

int main(int argc, char* argv[]) {
  if (initGNE(NO_NET, atexit)) {
    exit(1);
  }
  initConsole();
  setTitle("GNE Console Test/Example");

  TextConsole console( 5, 5, 40, 10 );

  console.setAutoRender( false );
  console << "Testing testing testing" << endl;
  console << "More testing" << endl;
  console << setw(15) << setfill('-') << 15 << endl;
  console.setContIndent(" -- ");
  console << " * Another line that is really long and is going " <<
    "to wrap around onto another line, using the new indent." << endl;
  console.update();
  console.setContIndent("  ");
  getch();

  console.setAutoRender( true );
  console << "Erasing console, then bringing it back." << endl;
  getch();
  console.erase();
  getch();
  console.redraw();
  console << "Clearing the console's text." << endl;
  getch();
  console.clear();

  console << "Now testing multithreaded locking:" << endl;
  ConsoleTest::sptr tester = ConsoleTest::create( console );
  tester->start();
  Thread::sleep( 250 );
  console << acquire << "This line should also be together."
    << endl << release;
  tester->join();
  getch();
  console.clear();

  console << "Now entering into interactive typing mode.  Keep in mind " <<
    "that the console is word-buffered, meaning you have to type in a " <<
    "delimiting character (like a space, dash, or return) before you see " <<
    "anything." << endl;
  console << "Use the ~ key to quit the mode." << endl;
  int val = getch();
  while ( val != '~' ) {
    if ( val == Console::ENTER )
      val = '\n';
    if ( val != Console::BACKSPACE )
      console << (char)val;
    val = getch();
  }

  console << endl << "Now erasing the console after a key is pressed." << endl;
  getch();
  console.erase();
  getch();

  return 0;
}
