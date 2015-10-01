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

#include <gnelib.h>
#include <cassert>
#include <climits>

using namespace std;
using namespace GNE;
using namespace Console;

class TimeClass : public TimerCallback {
protected:
  TimeClass(int x, int y, std::string ourName)
    : lastTime(Timer::getCurrentTime()), callNum(0), x(x), y(y), name(ourName) {
    gnedbgo( 5, "TimeClass created" );
  }

public:
  typedef SmartPtr<TimeClass> sptr;
  typedef WeakPtr<TimeClass> wptr;

  static sptr create( int x, int y, std::string ourName ) {
    return sptr( new TimeClass( x, y, ourName ) );
  }

  virtual ~TimeClass() {
    gnedbgo( 5, "TimeClass destroyed" );
  }

  void timerCallback() {
    Time currTime = Timer::getCurrentTime();
    Time diffTime = currTime - lastTime;
    lastTime = currTime;
    mlprintf(x, y, "(%i)Hello, I'm %s! change: %ius", callNum, name.c_str(), diffTime.getTotaluSec());
    callNum++;
  }

private:
  Time lastTime;
  int callNum;
  int x, y;
  std::string name;
};

/**
 * This is a strange, atypical class.  It's a TimerCallback that starts up a
 * Timer and listens to that.
 */
class CounterWatcher : public TimerCallback {
protected:
  CounterWatcher(int x, int y, int counterRate)
    : x(x), y(y) {
    counter = Counter::create();
    timer = Timer::create( counter, counterRate );
    timer->startTimer();
    gnedbgo( 5, "CounterWatcher created" );
  }

public:
  typedef SmartPtr<CounterWatcher> sptr;
  typedef WeakPtr<CounterWatcher> wptr;

  static sptr create( int x, int y, int counterRate ) {
    return sptr( new CounterWatcher( x, y, counterRate ) );
  }

  virtual ~CounterWatcher() {
    //Setting true here causes stopTimer to wait until the callbacks are
    //done, whereas setting false will not wait.
    timer->stopTimer(true);
    gnedbgo( 5, "CounterWatcher destroyed" );
  }

  void timerCallback() {
    mlprintf(x, y, "Count: %i", counter->getCount());
  }
private:
  int x, y;
  Counter::sptr counter;
  Timer::sptr timer;
};
  
int main() {
  //GNE::initDebug( DLEVEL1 | DLEVEL5, "extimerd.txt" );
  initGNE(NO_NET, atexit);
  initConsole();
  setTitle("GNE Timers Example");

  //Doing some tests on Time class
  mprintf("Time class tests:\n");
  Time t(0, 1000000);
  mprintf("%is, %ius\n", t.getSec(), t.getuSec());
  t += 1000001; //add a little over one second
  mprintf("%is, %ius\n", t.getSec(), t.getuSec());
  t.setSec(5);
  mprintf("%is, %ius\n", t.getSec(), t.getuSec());
  t = t + Time(3, 5500000);
  mprintf("%is, %ius\n", t.getSec(), t.getuSec());
  mprintf("Timer class tests, press a key to quit:\n");

  //try for some overflow tests.
  t.setSec( 0 );
  t.setuSec( 0 );
  t += INT_MAX;
  assert( t.getTotaluSec() == INT_MAX );
  assert( t.getuSec() == 483647 );
  assert( t.getSec() == 2147 );
  t += INT_MAX;
  assert( t.getuSec() == 967294 );
  assert( t.getSec() == 4294 );
  t = t + INT_MAX;
  assert( t.getuSec() == 450941 );
  assert( t.getSec() == 6442 );

  //check handling of negative numbers.
  t = Time( 0, -1 );
  assert( t.getTotaluSec() == -1 );
  assert( t.getSec() == -1 );
  assert( t.getuSec() == 999999 );

  assert( t == Time( 1, -1000001 ) );

  //Create the timers, which will destroy their callbacks when they die, since
  //we aren't keeping a SmartPtr to them.
  Timer::sptr t1 = Timer::create( TimeClass::create(3, 8, "Bob"), 1000 );
  Timer::sptr t2 = Timer::create( TimeClass::create(5, 10, "Sally"), 1250 );
  Timer::sptr t3 = Timer::create( TimeClass::create(1, 12, "Joe"), 200 );
  Timer::sptr t4 = Timer::create( CounterWatcher::create(40, 3, 10), 500 );

  //Start the timers
  t1->startTimer();
  assert(t1->isRunning());
  t2->startTimer();
  assert(t2->isRunning());
  t3->startTimer();
  assert(t3->isRunning());
  t4->startTimer();
  assert(t4->isRunning());

  getch(); //Wait for a keypress.

  mlprintf(0, 14, "Shutting down timers, please wait...");

  //these calls are optional.  When GNE shuts down it will shut all timers
  //down.  You can also use Timer::stopAll.
  t1->stopTimer(false);
  t2->stopTimer(false);

  //t1 through t4 should be shut down by GNE -- so we test this by "forgetting"
  // to stop t3 and t4 examine the extimerd.txt log file to be sure they stopped.
  //t3->stopTimer(false);
  //t4->stopTimer(false);

  //When GNE shuts down, it will wait up to (by default) 10 seconds for all
  //connections, timers, and threads to end.
  return 0;
}
