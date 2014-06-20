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

//Our includes have code in it.  Normally this is a bad thing, but to simplify
//the makefile process, each example only has one .cpp.

//This include file includes the custom packets that we are registering with
//GNE that we will send to signifiy game events.  We register them with the
//PacketParser in the main function right after initializing GNE.

/**
 * This packet represents a paddle movement and contains all of the methods
 * that are required by the GNE Packet interface.
 */
class PaddleMovement : public Packet {
public:
  PaddleMovement(int newLoc = 1) : Packet(ID), newy( (guint8)newLoc ) {
  }

  virtual ~PaddleMovement() {}

  static const int ID;

  int getSize() const {
    return Packet::getSize() + Buffer::getSizeOf(newy);
  }

  void writePacket(Buffer& raw) const {
    Packet::writePacket(raw);
    raw << newy;
  }

  void readPacket(Buffer& raw) {
    Packet::readPacket(raw);
    raw >> newy;
  }

  guint8 newy;
};

const int PaddleMovement::ID = PacketParser::MIN_USER_ID;

/**
 * This packet signifies that the remote side missed the ball, and that we
 * just scored a point.  It contains no data, but we create a new child of
 * the Packet class so that we can uniquely identify this type of packet.
 */
class BallMissed : public Packet {
public:
  BallMissed() : Packet(ID) {}
  virtual ~BallMissed() {}

  static const int ID;

  int getSize() const {
    return Packet::getSize();
  }

  void writePacket(Buffer& raw) const {
    Packet::writePacket(raw);
  }

  void readPacket(Buffer& raw) {
    Packet::readPacket(raw);
  }
};

const int BallMissed::ID = PaddleMovement::ID + 1;
