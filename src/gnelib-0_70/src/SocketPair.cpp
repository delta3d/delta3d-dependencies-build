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

#include "../include/gnelib/gneintern.h"
#include "../include/gnelib/SocketPair.h"
#include "../include/gnelib/Address.h"

namespace GNE {

SocketPair::SocketPair(NLsocket reliable, NLsocket unreliable)
: r(reliable), u(unreliable) {
}

SocketPair::~SocketPair() {
  disconnect();
}

void SocketPair::disconnect() {
  if (r != NL_INVALID) {
    nlClose(r);
    r = NL_INVALID;
  }
  if (u != NL_INVALID) {
    nlClose(u);
    u = NL_INVALID;
  }
}

Address SocketPair::getLocalAddress(bool reliable) const {
  NLaddress ret;
  if (reliable) {
    if (r != NL_INVALID)
      nlGetLocalAddr(r, &ret);
    else
      ret.valid = NL_FALSE;
  } else {
    if (u != NL_INVALID)
      nlGetLocalAddr(u, &ret);
    else
      ret.valid = NL_FALSE;
  }
  return Address(ret);
}

Address SocketPair::getRemoteAddress(bool reliable) const {
  NLaddress ret;
  if (reliable) {
    if (r != NL_INVALID)
      nlGetRemoteAddr(r, &ret);
    else
      ret.valid = NL_FALSE;
  } else {
    if (u != NL_INVALID)
      nlGetRemoteAddr(u, &ret);
    else
      ret.valid = NL_FALSE;
  }
  return Address(ret);
}

static void addStats(NLsocket s, ConnectionStats& st) {
  st.packetsSent += nlGetSocketStat(s, NL_PACKETS_SENT);
  st.bytesSent += nlGetSocketStat(s, NL_BYTES_SENT);
  st.avgBytesSent += nlGetSocketStat(s, NL_AVE_BYTES_SENT);
  st.maxAvgBytesSent += nlGetSocketStat(s, NL_HIGH_BYTES_SENT);
  st.packetsRecv += nlGetSocketStat(s, NL_PACKETS_RECEIVED);
  st.bytesRecv += nlGetSocketStat(s, NL_BYTES_RECEIVED);
  st.avgBytesRecv += nlGetSocketStat(s, NL_AVE_BYTES_RECEIVED);
  st.maxAvgBytesRecv += nlGetSocketStat(s, NL_HIGH_BYTES_RECEIVED);
  st.openSockets++;
}

ConnectionStats SocketPair::getStats(int reliable) const {
  ConnectionStats ret;
  memset((void*)&ret, 0, sizeof(ret));
  if (reliable != 0 && r != NL_INVALID) //Add in reliable socket stats
    addStats(r, ret);
  if (reliable <= 0 && u != NL_INVALID) //Add in unrel socket stats
    addStats(u, ret);
  return ret;
}

int SocketPair::rawRead(bool reliable, Buffer& buf) const {
  NLsocket act;
  if (reliable)
    act = r;
  else
    act = u;
  assert(act != NL_INVALID);

  buf.clear();
  int read = nlRead( act, (NLvoid*)buf.getData(), (NLint)buf.getCapacity() );
  
  //this if checks prevents an exception being thrown under forceful disconnect
  //which will leave the socket in a bad state
  if(read > 0) buf.setLimit( read );

  return read;
}

int SocketPair::rawWrite(bool reliable, const Buffer& buf) const {
  NLsocket act;
  if (reliable)
    act = r;
  else //if u is invalid, send over r anyways.
    act = (u != NL_INVALID) ? u : r;
  assert(act != NL_INVALID);

  return nlWrite(act, (const NLvoid*)buf.getData(), (NLint)buf.getPosition());
}

} //Namespace GNE




