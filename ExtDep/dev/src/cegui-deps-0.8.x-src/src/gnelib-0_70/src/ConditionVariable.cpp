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

#include "gneintern.h"

#include <gnelib/ConditionVariable.h>
#include <gnelib/Mutex.h>
#include <gnelib/Time.h>
#include <gnelib/Timer.h>

#include <limits>

#ifdef WIN32

namespace GNE {

//There appears to be a max() macro defined that is messing things up in
//at least MSVC.NET, and we don't use a max() define in this source file.
#undef max

//The WIN32 version of this code was adapted from Boost.  I believe this is
//within the license for Boost.

struct ConditionVariable::ConditionVariableData {
  HANDLE m_gate;
  HANDLE m_queue;
  HANDLE m_mutex;
  unsigned m_gone; // # threads that timed out and never made it to the m_queue
  unsigned long m_blocked; // # threads m_blocked m_waiting for the condition
  unsigned m_waiting; // # threads m_waiting no longer m_waiting for the condition but still
                      //   m_waiting to be removed from the m_queue
  
  ConditionVariableData() : m_gone(0), m_blocked(0), m_waiting(0) {}
};

ConditionVariable::ConditionVariable() {
  data = new ConditionVariableData();
  initBoostCode();
  ourMutex = true;
  mutex = new Mutex();
}

ConditionVariable::ConditionVariable(Mutex* m) {
  data = new ConditionVariableData();
  initBoostCode();
  ourMutex = false;
  mutex = m;
}

void ConditionVariable::initBoostCode() {
  data->m_gate = CreateSemaphore(0, 1, 1, 0);
  data->m_queue = CreateSemaphore(0, 0, std::numeric_limits<long>::max(), 0);
  data->m_mutex = CreateMutex(0, 0, 0);
  assert(data->m_gate && data->m_queue && data->m_mutex);
}

ConditionVariable::~ConditionVariable() {
  //Shutdown for boost code
  int res = 0;
  res = CloseHandle(data->m_gate);
  assert(res);
  res = CloseHandle(data->m_queue);
  assert(res);
  res = CloseHandle(data->m_mutex);
  assert(res);

  //Our shutdown code
  if (ourMutex)
    delete mutex;
  delete data;
}

void ConditionVariable::acquire() {
  mutex->acquire();
}

void ConditionVariable::release() {
  mutex->release();
}

void ConditionVariable::enter_wait() {
  int res = 0;
  res = WaitForSingleObject(data->m_gate, INFINITE);
  assert(res == WAIT_OBJECT_0);
  ++data->m_blocked;
  res = ReleaseSemaphore(data->m_gate, 1, 0);
  assert(res);
}

void ConditionVariable::wait() {
  enter_wait();
  release();

  int res = 0;
  res = WaitForSingleObject(data->m_queue, INFINITE);
  assert(res == WAIT_OBJECT_0);

  unsigned was_waiting=0;
  unsigned was_gone=0;

  res = WaitForSingleObject(data->m_mutex, INFINITE);
  assert(res == WAIT_OBJECT_0);
  was_waiting = data->m_waiting;
  was_gone = data->m_gone;
  if (was_waiting != 0)
  {
    if (--data->m_waiting == 0)
    {
      if (data->m_blocked != 0)
      {
        res = ReleaseSemaphore(data->m_gate, 1, 0); // open data->m_gate
        assert(res);
        was_waiting = 0;
      }
      else if (data->m_gone != 0)
        data->m_gone = 0;
    }
  }
  else if (++data->m_gone == (std::numeric_limits<unsigned>::max() / 2))
  {
    // timeout occured, normalize the data->m_gone count
    // this may occur if many calls to wait with a timeout are made and
    // no call to notify_* is made
    res = WaitForSingleObject(data->m_gate, INFINITE);
    assert(res == WAIT_OBJECT_0);
    data->m_blocked -= data->m_gone;
    res = ReleaseSemaphore(data->m_gate, 1, 0);
    assert(res);
    data->m_gone = 0;
  }
  res = ReleaseMutex(data->m_mutex);
  assert(res);

  if (was_waiting == 1)
  {
    for (/**/ ; was_gone; --was_gone)
    {
      // better now than spurious later
      res = WaitForSingleObject(data->m_queue, INFINITE);
      assert(res == WAIT_OBJECT_0);
    }
    res = ReleaseSemaphore(data->m_gate, 1, 0);
    assert(res);
  }

  acquire();
}

void ConditionVariable::timedWait(int ms) {
  enter_wait();
  release();

  unsigned int res = 0;
  res = WaitForSingleObject(data->m_queue, ms);
  assert(res != WAIT_FAILED && res != WAIT_ABANDONED);

  bool ret = (res == WAIT_OBJECT_0);

  unsigned was_waiting=0;
  unsigned was_gone=0;

  res = WaitForSingleObject(data->m_mutex, INFINITE);
  assert(res == WAIT_OBJECT_0);
  was_waiting = data->m_waiting;
  was_gone = data->m_gone;
  if (was_waiting != 0)
  {
    if (!ret) // timeout
    {
      if (data->m_blocked != 0)
        --data->m_blocked;
      else
        ++data->m_gone; // count spurious wakeups
    }
    if (--data->m_waiting == 0)
    {
      if (data->m_blocked != 0)
      {
        res = ReleaseSemaphore(data->m_gate, 1, 0); // open data->m_gate
        assert(res);
        was_waiting = 0;
      }
      else if (data->m_gone != 0)
        data->m_gone = 0;
    }
  }
  else if (++data->m_gone == (std::numeric_limits<unsigned>::max() / 2))
  {
    // timeout occured, normalize the data->m_gone count
    // this may occur if many calls to wait with a timeout are made and
    // no call to notify_* is made
    res = WaitForSingleObject(data->m_gate, INFINITE);
    assert(res == WAIT_OBJECT_0);
    data->m_blocked -= data->m_gone;
    res = ReleaseSemaphore(data->m_gate, 1, 0);
    assert(res);
    data->m_gone = 0;
  }
  res = ReleaseMutex(data->m_mutex);
  assert(res);

  if (was_waiting == 1)
  {
    for (/**/ ; was_gone; --was_gone)
    {
      // better now than spurious later
      res = WaitForSingleObject(data->m_queue, INFINITE);
      assert(res ==  WAIT_OBJECT_0);
    }
    res = ReleaseSemaphore(data->m_gate, 1, 0);
    assert(res);
  }

  acquire();
}

void ConditionVariable::timedWait(const Time& until) {
  Time t = until - Timer::getAbsoluteTime();
  int microSec = t.getTotaluSec();
  if (microSec <= 0) {
    //Return immediately because the time has already passed.
    return;
  } else {
    timedWait(microSec / 1000);
  }
}

void ConditionVariable::signal() {
  unsigned signals = 0;

  int res = 0;
  res = WaitForSingleObject(data->m_mutex, INFINITE);
  assert(res == WAIT_OBJECT_0);

  if (data->m_waiting != 0) // the data->m_gate is already closed
  {
    if (data->m_blocked == 0)
    {
      res = ReleaseMutex(data->m_mutex);
      assert(res);
      return;
    }

    ++data->m_waiting;
    --data->m_blocked;
    signals = 1;
  }
  else
  {
    res = WaitForSingleObject(data->m_gate, INFINITE);
    assert(res == WAIT_OBJECT_0);
    if (data->m_blocked > data->m_gone)
    {
      if (data->m_gone != 0)
      {
        data->m_blocked -= data->m_gone;
        data->m_gone = 0;
      }
      signals = data->m_waiting = 1;
      --data->m_blocked;
    }
    else
    {
      res = ReleaseSemaphore(data->m_gate, 1, 0);
      assert(res);
    }
  }

  res = ReleaseMutex(data->m_mutex);
  assert(res);

  if (signals)
  {
    res = ReleaseSemaphore(data->m_queue, signals, 0);
    assert(res);
  }
}

void ConditionVariable::broadcast() {
  unsigned signals = 0;

  int res = 0;
  res = WaitForSingleObject(data->m_mutex, INFINITE);
  assert(res == WAIT_OBJECT_0);

  if (data->m_waiting != 0) // the data->m_gate is already closed
  {
    if (data->m_blocked == 0)
    {
      res = ReleaseMutex(data->m_mutex);
      assert(res);
      return;
    }

    data->m_waiting += (signals = data->m_blocked);
    data->m_blocked = 0;
  }
  else
  {
    res = WaitForSingleObject(data->m_gate, INFINITE);
    assert(res == WAIT_OBJECT_0);
    if (data->m_blocked > data->m_gone)
    {
      if (data->m_gone != 0)
      {
        data->m_blocked -= data->m_gone;
        data->m_gone = 0;
      }
      signals = data->m_waiting = data->m_blocked;
      data->m_blocked = 0;
    }
    else
    {
      res = ReleaseSemaphore(data->m_gate, 1, 0);
      assert(res);
    }

    res = ReleaseMutex(data->m_mutex);
    assert(res);

    if (signals)
    {
      res = ReleaseSemaphore(data->m_queue, signals, 0);
      assert(res);
    }
  }
}

} //namespace GNE

// ----------- BEGIN UNIX CODE -------------
#else

#include "MutexData.h"

namespace GNE {

struct ConditionVariable::ConditionVariableData {
  pthread_cond_t cond;
};

ConditionVariable::ConditionVariable() {
  data = new ConditionVariableData();
  valassert(pthread_cond_init( &data->cond, NULL ), 0);
  ourMutex = true;
  mutex = new Mutex();
}

ConditionVariable::ConditionVariable(Mutex* m) {
  data = new ConditionVariableData();
  valassert(pthread_cond_init( &data->cond, NULL ), 0);
  mutex = m;
  ourMutex = false;
}

ConditionVariable::~ConditionVariable() {
  valassert(pthread_cond_destroy( &data->cond ), 0);
  if (ourMutex)
    delete mutex;
  delete data;
}

void ConditionVariable::acquire() {
  mutex->acquire();
}

void ConditionVariable::release() {
  mutex->release();
}

void ConditionVariable::wait() {
#ifdef _DEBUG
  mutex->markReleased();
#endif
  valassert(pthread_cond_wait(&data->cond, &mutex->data->mutex), 0);
#ifdef _DEBUG
  mutex->markAcquired();
#endif
}

void ConditionVariable::timedWait(int ms) {
  Time t = Timer::getAbsoluteTime();
  t += ms*1000;
  timedWait(t);
}

void ConditionVariable::timedWait(const Time& until) {
  timespec tv;
  tv.tv_sec = until.getSec();
  tv.tv_nsec = until.getuSec() * 1000;
  pthread_cond_timedwait(&data->cond, &(mutex->data->mutex), &tv);
}

void ConditionVariable::signal() {
  valassert(pthread_cond_signal( &data->cond ), 0);
}

void ConditionVariable::broadcast() {
  valassert(pthread_cond_broadcast( &data->cond ), 0);
}

} //end namespace GNE

#endif

