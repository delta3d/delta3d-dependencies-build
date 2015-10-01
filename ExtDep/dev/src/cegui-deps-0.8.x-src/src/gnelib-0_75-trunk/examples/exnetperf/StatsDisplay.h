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

/**
 * StatsDisplay is a helper class for exnetperf which waits for some time
 * then updates stats.  The waiting is done because the faster we update the
 * screen, the more time we take away from network performance.  The less we
 * wait the better the feedback to the user.
 */

#include <gnelib.h>

using namespace std;
using namespace GNE;
using namespace GNE::PacketParser;
using namespace GNE::Console;

//This keeps track of some screen positions when can write to.
//Essentially makes tiles out of the screen.
struct Pos {
  Pos( int x, int y ) : x(x), y(y), packetsIn(NULL), packetsOut(NULL) {}

  int x, y;
  Connection::sptr conn;
  int* packetsIn;
  int* packetsOut;
};
static Pos gpos(0, 10); //global stats position
static int positionsLength = 3;
static Pos positions[] = {
  Pos(0, 15), Pos(0, 22), Pos(0, 29), Pos(0, 36)
};

class StatsDisplay : public TimerCallback {
public:
  typedef SmartPtr<StatsDisplay> sptr;
  typedef WeakPtr<StatsDisplay> wptr;

protected:
  StatsDisplay() {
  }

public:
  /**
   * Sets up a StatsDisplay that updates the screen every "rate" milliseconds.
   */
  static sptr create( int rate ) {
    sptr ret( new StatsDisplay() );
    ret->timer = Timer::create(ret, rate);
    return ret;
  }

  virtual ~StatsDisplay() {
  }

  /**
   * Starts the timer and starts displaying stats.
   */
  void startDisplay() {
    timer->startTimer();
  }

  /**
   * Stops what startDisplay started.
   */
  void stopDisplay() {
    timer->stopTimer(false);
  }

  /**
   * Adds a connection to the display list, returning true if there is not
   * enough screen space left.  In this case, the connection was not added
   * and stats will not be displayed.
   *
   * @param conn the connection to add.
   * @param packetsIn a pointer to a place to get high-level packets in
   * @param packetsOut similar to packetsIn
   */
  bool addConn(const Connection::sptr& conn, int* packetsIn, int* packetsOut) {
    //Since we have multiple exit points, we use this convience class.
    LockMutex lock(sync);

    Pos* pos = findPos( Connection::sptr() );
    if (pos != NULL) {
      pos->conn = conn;
      pos->packetsIn = packetsIn;
      pos->packetsOut = packetsOut;
      return false;
    }

    return true;
  }

  /**
   * Deletes a connection from the display list.  If the connection is not in
   * the list, this function has no effect.
   */
  void delConn(const Connection::sptr& conn) {
    sync.acquire();
    Pos* pos = findPos(conn);
    if (pos != NULL) {
      pos->conn.reset();
      pos->packetsIn = pos->packetsOut = NULL;

      //Notify the user that the current screen location has finished its job
      //(for now at least) by printing disconnected over the IP addr.
      //We don't delete all of the data in case the user wants to trap the
      //text to keep the information.
      mlprintf(pos->x, pos->y, "* disconnected *  ");
    }
    sync.release();
  }

  /**
   * The callback function that updates the screen.
   */
  void timerCallback() {
    sync.acquire();
    for (int c = 0; c < positionsLength; ++c)
      if (positions[c].conn)
        updateStats(positions[c]);
    updateGlobalStats();
    sync.release();
  }

  /**
   * Redraws the stats for one connection.
   */
  void updateStats(const Pos& ourPos) {
    const Connection::sptr& conn = ourPos.conn;

    ConnectionStats all = conn->getStats(-1);
    ConnectionStats rel = conn->getStats(1);
    ConnectionStats unrel = conn->getStats(0);
    //C-style I/O so much nicer in this case over iostreams, eh?
    //Not that the C-style isn't that nice.  HTML would be our best choice
    //for formatting this data but we aren't in a web browser, are we ;) ?
    mlprintf(ourPos.x, ourPos.y, "%-18s%10s%10s%10s%11s%10s%10s",
      conn->getRemoteAddress(true).toString().c_str(), "in:tot =" , "rel +", "unrel",
      "out:tot =", "rel +", "unrel");
    mlprintf(ourPos.x, ourPos.y+1, "%-18s%10d%31d",
      "HiLvlPkts", *ourPos.packetsIn, *ourPos.packetsOut);

    mlprintf(ourPos.x, ourPos.y+2, "%-18s%10d%10d%10d%11d%10d%10d",
      "bytes", all.bytesRecv, rel.bytesRecv, unrel.bytesRecv,
      all.bytesSent, rel.bytesSent, unrel.bytesSent);
    mlprintf(ourPos.x, ourPos.y+3, "%-18s%10d%10d%10d%11d%10d%10d",
      "bytes/sec", all.avgBytesRecv, rel.avgBytesRecv, unrel.avgBytesRecv,
      all.avgBytesSent, rel.avgBytesSent, unrel.avgBytesSent);
    mlprintf(ourPos.x, ourPos.y+4, "%-18s%10d%10d%10d%11d%10d%10d",
      "max burst b/s", all.maxAvgBytesRecv, rel.maxAvgBytesRecv, unrel.maxAvgBytesRecv,
      all.maxAvgBytesSent, rel.maxAvgBytesSent, unrel.maxAvgBytesSent);

    mlprintf(ourPos.x, ourPos.y+5,
      "Current outgoing rate limit is %d  (remote limit %d)     ",
      conn->stream().getCurrOutRate(), conn->stream().getRemoteOutLimit());
  }

  /**
   * Redraws the global stats.
   */
  void updateGlobalStats() {
    ConnectionStats all = GNE::getGlobalStats();
    mlprintf(gpos.x, gpos.y, "%-18s%15s%15s", "global", "in:tot", "out:tot");
    mlprintf(gpos.x, gpos.y+1, "%-18s%15d%15d", "tot xfer",
      all.bytesRecv, all.bytesSent);
    mlprintf(gpos.x, gpos.y+2, "%-18s%15d%15d", "curr rate",
      all.avgBytesRecv, all.avgBytesSent);
    mlprintf(gpos.x, gpos.y+3, "%-18s%15d%15d", "max burst",
      all.maxAvgBytesRecv, all.maxAvgBytesSent);
  }

private:
  /**
   * Finds the first screen position used by conn.  If conn is NULL this is
   * OK -- it will find the first empty position.  Returns NULL on error.
   * sync should already be aquired here so we don't reacquire it.
   */
  Pos* findPos(const Connection::sptr& conn) {
    for (int c = 0; c < positionsLength; ++c)
      if (positions[c].conn == conn)
        return &positions[c];
    //If we reach here then the loop failed to find a pos.
    return NULL;
  }

  Timer::sptr timer;

  Mutex sync;
};
