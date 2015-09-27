#ifndef _MUTEXDATA_H_
#define _MUTEXDATA_H_

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

//This header file is _NOT_ meant to be included into user code!

#include "gneintern.h"
#include <gnelib/Thread.h>

#ifdef WIN32
  #define MUTEX_TYPE CRITICAL_SECTION
  #define MUTEX_PTR LPCRITICAL_SECTION
#else
  #define MUTEX_TYPE pthread_mutex_t
  #define MUTEX_PTR pthread_mutex_t*
#endif

namespace GNE {

struct Mutex::MutexData {
  MUTEX_TYPE mutex;

#ifdef _DEBUG
  MUTEX_TYPE dbgMutex;
  int lockCount;
  Thread* owner;
#endif
};

} //namespace GNE

#endif
