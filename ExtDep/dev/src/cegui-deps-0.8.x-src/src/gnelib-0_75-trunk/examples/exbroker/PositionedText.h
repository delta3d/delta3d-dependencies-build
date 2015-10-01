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
 * PositionedText is the example class we use to "replicate."  This header
 * also contains the associated packets for PositionedText.
 *
 * The packets given are a little more verbose than typical, to give the
 * object brokering some interesting test/example situtations.
 */

/**
 * Contains all information to completely create a PositionedText object.
 */
class PositionedTextPacket : public Packet {
public:
  PositionedTextPacket() : Packet(ID), x(0), y(0) {
  }

  PositionedTextPacket( string msg, int x, int y )
    : Packet(ID), msg(msg), x((guint8)x), y((guint8)y) {
  }

  virtual ~PositionedTextPacket() {
  }

  virtual int getSize() const {
    return Packet::getSize() + Buffer::getSizeOf( msg ) +
           Buffer::getSizeOf( x ) + Buffer::getSizeOf( y );
  }

  void writePacket( Buffer& raw ) const {
    Packet::writePacket( raw );
    raw << x << y << msg;
  }

  void readPacket( Buffer& raw ) {
    Packet::readPacket( raw );
    raw >> x >> y >> msg;
  }

  string msg;

  guint8 x, y;

  static int ID;
};

int PositionedTextPacket::ID = PacketParser::MIN_USER_ID;

/**
 * The PositionedTextPositionUpdatePacket contains update information about
 * the position of the PositionedText object.
 */
class PositionedTextPositionUpdatePacket : public Packet {
public:
  PositionedTextPositionUpdatePacket() : Packet(ID), x(0), y(0) {
  }

  PositionedTextPositionUpdatePacket( int x, int y )
    : Packet(ID), x((guint8)x), y((guint8)y) {
  }

  virtual ~PositionedTextPositionUpdatePacket() {
  }

  virtual int getSize() const {
    return Packet::getSize() +  Buffer::getSizeOf( x ) + Buffer::getSizeOf( y );
  }

  void writePacket( Buffer& raw ) const {
    Packet::writePacket( raw );
    raw << x << y;
  }

  void readPacket( Buffer& raw ) {
    Packet::readPacket( raw );
    raw >> x >> y;
  }

  guint8 x, y;

  static int ID;
};

int PositionedTextPositionUpdatePacket::ID = PacketParser::MIN_USER_ID + 1;

/**
 * The PositionedTextPositionUpdatePacket contains update information about
 * the text of the PositionedText object.
 */
class PositionedTextTextUpdatePacket : public Packet {
public:
  PositionedTextTextUpdatePacket() : Packet(ID) {
  }

  PositionedTextTextUpdatePacket( string msg )
    : Packet(ID), msg(msg) {
  }

  virtual ~PositionedTextTextUpdatePacket() {
  }

  virtual int getSize() const {
    return Packet::getSize() + Buffer::getSizeOf( msg );
  }

  void writePacket( Buffer& raw ) const {
    Packet::writePacket( raw );
    raw << msg;
  }

  void readPacket( Buffer& raw ) {
    Packet::readPacket( raw );
    raw >> msg;
  }

  string msg;

  static int ID;
};

int PositionedTextTextUpdatePacket::ID = PacketParser::MIN_USER_ID + 2;

/**
 * The PositionedText object contains a located string on the screen, and
 * manages drawing and moving it.
 */
class PositionedText : public NetworkObject {
public:
  PositionedText() : dead(false), drawn(false), x(0), y(0) {
  }

  PositionedText( string msg, int x, int y )
    : dead(false), drawn(false), x(x), y(y), msg(msg) {
  }

  PositionedText( int objId, string msg, int x, int y )
    : NetworkObject( objId ), dead(false), drawn(false), x(x), y(y), msg(msg) {
  }

  static NetworkObject* createFromPacket( int objId, const Packet& packet ) {
    assert( packet.getType() == PositionedTextPacket::ID );
    const PositionedTextPacket& ptp = (const PositionedTextPacket&)packet;

    return new PositionedText( objId, ptp.msg, ptp.x, ptp.y );
  }

  virtual ~PositionedText() {
  }

  bool isDead() const {
    return dead;
  }

  bool isDrawn() const {
    return drawn;
  }

  void setText( string newMsg ) {
    if ( drawn )
      eraseImpl();

    msg = newMsg;

    if ( drawn )
      draw();
  }

  void setPos( int newX, int newY ) {
    if ( drawn )
      eraseImpl();

    x = newX;
    y = newY;

    if ( drawn )
      draw();
  }

  void draw() {
    drawn = true;
    //We need to do the stringstream thing because we have to determine the
    //size of the final output string, so erase can work properly.
    ostringstream temp;
    temp << getObjectId() << ": " << msg;
    const string& tempStr = temp.str();
    drawnSize = (int)tempStr.length();

    gout << acquire << moveTo(x, y) << tempStr << flush << release;
  }

  void erase() {
    eraseImpl();
    drawn = false;
  }

  virtual Packet* createCreationPacket() {
    return new PositionedTextPacket( msg, x, y );
  }

  virtual Packet* createUpdatePacket( const void* param ) {
    const bool& updateText = *((const bool*)(param));
    if ( updateText ) {
      return new PositionedTextTextUpdatePacket( msg );
    } else {
      return new PositionedTextPositionUpdatePacket( x, y );
    }
  }

  virtual Packet* createDeathPacket() {
    //server side only call
    return NULL;
  }

  virtual void onDeregistration( int oldId ) {
    ostringstream deathmsg;
    deathmsg << "XXX " << oldId << " died XXX";
    const string& s = deathmsg.str();
    dead = true;
    msg = string( s, 0, msg.length() );
    if ( drawn ) {
      erase();
      draw();
    }
  }

  virtual void incomingUpdatePacket( const Packet& packet ) {
    int type = packet.getType();
    if ( type == PositionedTextPositionUpdatePacket::ID ) {
      const PositionedTextPositionUpdatePacket& p =
        (const PositionedTextPositionUpdatePacket&)packet;
      setPos( p.x, p.y );

    } else if ( type == PositionedTextTextUpdatePacket::ID ) {
      const PositionedTextTextUpdatePacket& p =
        (const PositionedTextTextUpdatePacket&)packet;
      setText( p.msg );

    } else {
      assert( false );
    }
  }

  virtual void incomingDeathPacket( const Packet* packet ) {
    //Work for the object "dying" can be done in either this method, in the
    //onDeregistration event, or some in both places.  This happens only for
    //the client side.
  }

private:
  void eraseImpl() {
    if ( drawn ) {
      //drawnSize was set in the draw function.
      string s( drawnSize, ' ' );
      gout << acquire << moveTo(x, y) << s << flush << release;
    }
  }

  bool dead;

  bool drawn;
  int drawnSize;
  int x, y;
  string msg;
};
