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

#include <gnelib/GNEDebug.h>
#include <gnelib/Mutex.h>
#include <gnelib/Lock.h>
#include <gnelib/Thread.h>
#include <ctime>
#include <cstring>

namespace GNE {

static const int BUF_SIZE = 512;

static int dbgLevelMask = 0;
static FILE* logFile = NULL;
static Mutex sync;
static char* buf = NULL;
static bool initialized = false;

bool initDebug(int levelMask, const char* fileName) {
  LockMutex lock( sync );

  dbgLevelMask = levelMask;

  buf = new char[BUF_SIZE];
  memset( buf, 0, BUF_SIZE );
  if (fileName == NULL) {
    time_t now = time(NULL);
    struct tm *t = localtime (&now);
    strftime (buf, 100, "gne%H'%M'%S.log", t);
  } else
    strncpy(buf, fileName,BUF_SIZE-1);

  logFile = fopen(buf, "wt");
  if (!logFile) {
    delete[] buf;
    buf = NULL;
    return true;
  }

  initialized = true;
  return false;
}

void killDebug() {
  LockMutex lock( sync );

  if (logFile != NULL)
    fclose(logFile);
  delete[] buf;

  logFile = NULL;
  buf = NULL;

  initialized = false;
}

void doTrace(int level, const char* fn, int lineno, const char* msg, ...) {
  if (((dbgLevelMask & DLEVEL1) && level == 1) ||
      ((dbgLevelMask & DLEVEL2) && level == 2) ||
      ((dbgLevelMask & DLEVEL3) && level == 3) ||
      ((dbgLevelMask & DLEVEL4) && level == 4) ||
      ((dbgLevelMask & DLEVEL5) && level == 5)) {
    va_list arg;  
    va_start(arg, msg);

    //Get the current thread's name:
    Thread::sptr currThr = Thread::currentThread();
    std::string thrName;
    if (currThr) {
      thrName = currThr->getName();
    } else {
      //The main thread has no Thread object.
      thrName = "main";
    }

    LockMutexEx lock( sync );
    if ( initialized ) {
      vsnprintf(buf, BUF_SIZE-1, msg, arg);
      buf[ BUF_SIZE-1 ] = 0;

      //Remove the path to the file, to conserve line width.
      const char* temp = strrchr(fn, '\\'); //Try Microsoft style path
      if (temp == NULL) {
        temp = strrchr(fn, '/');      //Try UNIX style path
        if (temp == NULL)
          temp = buf;                 //If all else fails...
        else
          temp++;
      } else
        temp++;
      //The longest filename is ConnectionEventGenerator.cpp, which is 28 chars.
      fprintf(logFile, "%28s, line %4i, thrd %8s: %s\n",
        temp, lineno, thrName.c_str(), buf);
      fflush(logFile); //Try to be resiliant to errors.
    }
    lock.release();

    va_end(arg);
  }
}

}
