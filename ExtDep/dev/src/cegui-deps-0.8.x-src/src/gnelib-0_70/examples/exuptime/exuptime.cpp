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

#include <gnelib.h>
#ifdef OLD_CPP
#include <iostream>
#else
#include <ostream> //for endl
#endif

using namespace std; //for endl
using namespace GNE;
using namespace GNE::Console;

int main() {
  initGNE(NO_NET, atexit);
  initConsole(atexit);
  setTitle("GNE Timer Example");
  
  gout << "The time in seconds, is:" << endl;
  gout << "Time is from some arbitrary point in the past." << endl;
  gout << "In Windows, this is usually the system uptime." << endl;
  while (!kbhit()) {
    Time t = Timer::getCurrentTime();
    //The move operation will be "executed" when the stream is next flushed,
    //and gout is line-buffered so it flushes on endl as well as the usual
    //methods.
    gout << moveTo(25, 0) << t << endl;
  }

  return 0;
}


