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

//NOTES ON THREADS:
// Threads will manage their own memory, so they will be deleted when they
//  have stopped running and you don't have references to it anymore.
// You MUST call the "setThisPointer" method in your static creation
//  function.
// Threads MUST be managed by a SmartPtr.
// If you get an assert failure of "this_" it is because you didn't call
//  the "setThisPointer" method.

#include <gnelib.h>
#include <cassert>
#include <climits>

#include <sys/timeb.h>

using namespace GNE;
using namespace GNE::Console;

class HelloWorld : public Thread {
public:
  //define these typedefs just for convienence
  typedef SmartPtr<HelloWorld> sptr;
  typedef WeakPtr<HelloWorld> wptr;

protected:
  //we can't allow straight construction of this object
  HelloWorld( std::string myName, Mutex& mutexToTest )
    : Thread(myName), testMutex(mutexToTest) {
    mprintf("%s is born\n", myName.c_str());
  }

public:
  /**
   * Creates a new HelloWorld thread.
   */
  static sptr create( std::string myName, Mutex& mutexToTest ) {
    sptr ret( new HelloWorld( myName, mutexToTest ) );
    ret->setThisPointer( ret );
    return ret;
  }

  virtual ~HelloWorld() {
    mprintf("%s dies.\n", getName().c_str());
  }

protected:
  void run() {
    //Note that if we were sitting in an infinite loop, we would have to
    //respond to the shutdown variable, as shown in comments.  The commented
    //code would be the proper code if we wanted to repeat an action forever.
    //You would call shutDown then join on this thread to stop it in this
    //case.
    //while (!shutdown) {
    //  do_stuff();
    //}

    //Test the mutex we were given.  In normal operation the acquire should
    //not deadlock.  If it does there was a problem with unlocking the mutex
    //in the main thread.
    //The sleeps are to give the other threads a chance to go.  We should
    //never see two threads given the same mutex intertwine their prints.
    testMutex.acquire();

    mprintf("Hello World!  My name is %s.\n", getName().c_str());
    Thread::sleep(50);  //sleep(50) will work too, Thread:: is not needed...

    mprintf(" %s Ref: %x %x\n", getName().c_str(), Thread::currentThread().get(), this);

    assert(Thread::currentThread().get() == this);
    assert(Thread::currentThread() == getThisPointer() );

    testMutex.release();
  }

private:
  //We try to acquire this mutex just to test it to see if it was really
  //unlocked in the main thread.
  Mutex& testMutex;
};

class WaitingThread : public Thread {
public:
  //define these typedefs just for convienence
  typedef SmartPtr<WaitingThread> sptr;
  typedef WeakPtr<WaitingThread> wptr;

  virtual ~WaitingThread() {}

  static sptr create() {
    sptr ret( new WaitingThread() );
    ret->setThisPointer( ret );
    return ret;
  }

protected:
  WaitingThread() {}

  void run() {
    sleep(1000);
  }
};

int main(int argc, char* argv[]) {
  initGNE(NO_NET, atexit);
  initConsole(false);
  setTitle("GNE Threads Example");

  mprintf("Testing to see if recursive locks work:");
  Mutex test;
  test.acquire();
  test.acquire();
  test.release();
  test.release();
  mprintf(" success.\n");

  Mutex test2;
  mprintf("Testing recursive locks with LockMutex:");
  try {
    //The LockMutex class locks the mutex when it is created.  When it is
    //destroyed the mutex is unlocked, and this is useful if a function has
    //mutliple return statements or throws exceptions.  You would never want
    //to use them as they are here (nested).  Only one LockMutex is ever
    //needed.
    LockMutex lock(test2);
    LockMutex lock2(test2);

    //When we throw an exception, variables in this block like lock and lock2
    //will be destroyed, and when a LockMutex is destroyed it unlocked the
    //mutex that it locked when it was created.
    throw 0;
  } catch (...) {
  }
  mprintf(" success.\n");

  //We make the HelloWorld threads, giving them some mutexes to test.  If two
  //threads are using the same mutex, they can't go at the same time.  So all
  //of Sally's statements should come before or after all of Joe's.  Bob uses
  //a different mutex so his statements will be mixed in with Sally's and
  //Joe's.
  HelloWorld::sptr bob = HelloWorld::create("Bob", test);
  assert( !bob->hasStarted() );
  assert( !bob->isRunning() );
  bob->start();      //Tells bob to start his job.
  bob.reset();
  //There is never a need to reset explicitly, but we do this to show that
  //you don't need to keep any pointers to Threads after you start them.
  //In the old GNE API, this was equivalent to detach(true)

  HelloWorld::sptr sally = HelloWorld::create("Sally", test2);
  sally->start();

  HelloWorld::sptr joe = HelloWorld::create("Joe", test2);
  joe->start();

  assert(sally->hasStarted());
  assert(sally->isRunning()); //Sally should be running.  Note this is true
                              //because sally->start() was called, and not
                              //because the thread has ACTUALLY started
                              //executing by the OS having given it any CPU
                              //time.
  mprintf("Waiting for Sally to end.\n");
  sally->join(); //we must either join or detach every thread.
  mprintf("Sally ended.  Killing Sally.\n");
  assert(!sally->isRunning());
  //In the old API, you used to have to manually delete Sally, but no need to
  //anymore.  We test deleting her explicitly through a reset call, but it is
  //not needed.
  sally.reset();

  mprintf("Sally died.  Now waiting for Joe to end.\n");

  //A busy wait is a very bad idea.  You should always use join, but isRunning
  //is possibly if you want to check for when joe dies while doing other stuff.
  while (joe->isRunning()) {}
  mprintf("Joe has ended.\n");

  //Sleep, measuring our sleep time
  Time lastTime = Timer::getCurrentTime();

  mprintf("Sleeping for 2459 milliseconds.\n");
  Thread::sleep(2459);

  Time diffTime = Timer::getCurrentTime();
  diffTime = diffTime - lastTime;

  mprintf("GNE timers report sleeping time of %i microseconds (us)\n", diffTime.getTotaluSec());
  
  mprintf("Now testing Thread::waitForAllThreads.\n");
  WaitingThread::create()->start();
  //this should timeout as the waiter thread waits for 1000 ms.
  bool timeout = Thread::waitForAllThreads(150);
  if (timeout)
    mprintf("Thread::waitForAllThreads timed out properly.\n");
  else
    mprintf("Thread::waitForAllThreads method failed.\n");

  //The waiter thread should definitely finish during this call.
  timeout = Thread::waitForAllThreads(INT_MAX);
  if (timeout)
    mprintf("Thread::waitForAllThreads method failed.\n");
  else
    mprintf("Thread::waitForAllThreads 2nd call completed successfully.\n");
  
  mprintf( "You should see joe die after you press a key (when main ends), if you have\n" );
  mprintf( " the window stay open after the program exits.\n" );
  mprintf( "Press a key to continue.\n" );
  getch();

  //At this point, all threads that are running will be terminated.  When
  //main exits, everything goes.  Use join if you want to guarantee your
  //threads have exited, or use waitForAllThreads to definitively verify that
  //detached threads have ended.
  //The threads will be FORCEFULLY terminated so this would be an abnormal
  //program close if any threads are still running, and their destructors
  //won't get called!
  return 0;
}
