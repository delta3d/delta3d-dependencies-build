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

//This include file includes the classes we have inherited from
//ConnectionListener and ServerConnectionListener.

/**
 * The PongClient is suitable for both sides of the connection, since this
 * implementation of pong is a very simple VERY trusting peer-to-peer network
 * game.
 *
 * It is also a PaddleListener so it can get events from the game logic to
 * know when the game state has changed, or a point has been scored.
 */
class PongClient : public ConnectionListener, public PaddleListener {
public:
  typedef SmartPtr<PongClient> sptr;
  typedef WeakPtr<PongClient> wptr;

protected:
  PongClient(Player* RemotePlayer, Player* LocalPlayer)
    : remotePlayer(RemotePlayer), localPlayer(LocalPlayer) {}

public:
  /**
   * The PongClient requires a paddle passed to be designated as its
   * associated network player.  If note is not NULL, then that CV is notifed
   * when a connection is made (this is for the server to sleep for a client
   * to enter).  The localPlayer is passed so that we may accredit him with
   * points when the remote paddle misses the ball.
   */
  static sptr create( Player* RemotePlayer, Player* LocalPlayer ) {
    return sptr( new PongClient( RemotePlayer, LocalPlayer ) );
  }

  ~PongClient() {}

  Connection::sptr getConnection() {
    return ourConn;
  }

  void onExit( Connection& conn ) {
    mlprintf(0, 24, "Remote player quit.  Press q to exit.");
  }

  void onConnect(SyncConnection& conn) {
    ourConn = conn.getConnection();

    //Do connection negotiation here.  If it fails, onConnectFailure will be
    //called.  Any interaction we have will conn2 can throw an exception.
    //The SyncConnection does all of the error checking for us.

    //Create a CustomPacket which we will use to send and receive primitive
    //data types.  SyncConnection can only send GNE packet types, and a
    //CustomPacket wraps a RawPacket, allowing us to send RawPackets back and
    //forth.
    CustomPacket buf;

    //First, read from the server if there is a player slot open and we are
    //accepted.  If not, throw a connection refused error.
    gbool accepted;
    conn >> buf;
    buf.getBuffer() >> accepted;
    if (!accepted) {
      conn.disconnect();
      throw Error(Error::ConnectionRefused);
    }

    //If we are accepted, we should be receiving the remote player's name.
    conn >> buf;
    string remoteName;
    buf.getBuffer() >> remoteName;
    remotePlayer->setName(remoteName);

    //Now we should send our name.
    buf.clear();
    buf.getBuffer() << localPlayer->getName();
    conn << buf;

    //Now we are ready to play pong!
  }

  void onNewConn(SyncConnection& conn) {
    ourConn = conn.getConnection();

    CustomPacket buf;
    //Tell the client that they have been accepted
    buf.getBuffer() << gTrue;
    conn << buf;
    //and send them our name.
    buf.clear();
    buf.getBuffer() << localPlayer->getName();
    conn << buf;

    //Now we wait for the client's name.
    conn >> buf;

    string remoteName;
    buf.getBuffer() >> remoteName;
    remotePlayer->setName(remoteName);
  }

  void onReceive( Connection& conn ) {
    Packet* next = conn.stream().getNextPacket();
    while (next != NULL) {
      int type = next->getType();
      if (type == PaddleMovement::ID) {
        //gnedbgo1(1, "paddleMoved %d received", ((PaddleMovement*)next)->newy);
        remotePlayer->paddle().changePosition(((PaddleMovement*)next)->newy);

      } else if (type == BallMissed::ID) {
        localPlayer->incrementScore();

      } else if (type == PingPacket::ID) {
        //We reply to ping requests, and check ping times on replies.
        PingPacket& ping = *((PingPacket*)next);
        if (ping.isRequest()) {
          ping.makeReply();
          conn.stream().writePacket(ping, true);
        } else {
          mlprintf(63, 24, "Ping: %ss",
            ping.getPingInformation().pingTime.toString().c_str());
        }

      } else {
        mlprintf(0, 24, "Unexpected packet type %d received!", type);
      }

      delete next;
      next = conn.stream().getNextPacket();
    }
  }

  //These next two functions are from us being a PaddleListener
  void paddleMoved(int newy) {
    //gnedbgo1(1, "paddleMoved %d sent", newy);
    //The paddle has moved.  Now let's tell the other side about that.
    PaddleMovement packet;
    packet.newy = newy;
    ourConn->stream().writePacket(packet, true);
  }

  void ballMissed() {
    //We missed the ball.  Now let's tell the other side about that.
    BallMissed packet;
    ourConn->stream().writePacket(packet, true);
  }

  void onFailure( Connection& conn, const Error& error ) {
    mlprintf(0, 24, "Socket failure: %s   ", error.toString().c_str());
    //No need to disconnect, this has already happened on a failure.
  }

  void onError( Connection& conn, const Error& error ) {
    mlprintf(0, 24, "Socket error: %s   ", error.toString().c_str());
    conn.disconnect();//For simplicity we treat even normal errors as fatal.
  }

  void onConnectFailure( Connection& conn, const Error& error ) {
    gout << "Connection to server failed." << endl;
    gout << "  GNE reported error: " << error << endl;
  }

private:
  Connection::sptr ourConn;

  Player* remotePlayer;
  Player* localPlayer;
};

/**
 * This is a class that the server side uses to refuse a client if one is
 * already connected.
 */
class RefuseClient : public ConnectionListener {
public:
  typedef SmartPtr<RefuseClient> sptr;
  typedef WeakPtr<RefuseClient> wptr;

public:
  static sptr create() {
    return sptr( new RefuseClient() );
  }

  void onNewConn(SyncConnection& conn) {
    CustomPacket buf;
    //Tell the client that they have been refused
    buf.getBuffer() << gFalse;
    conn << buf;
    conn.disconnect();
    throw Error(Error::ConnectionRefused);
  }
private:
};

class OurListener : public ServerConnectionListener {
public:
  typedef SmartPtr<OurListener> sptr;
  typedef WeakPtr<OurListener> wptr;

protected:
  OurListener(Player* RemotePlayer, Player* LocalPlayer)
    : remotePlayer(RemotePlayer), localPlayer(LocalPlayer), accept(true) {
  }

public:
  /**
   * This listener takes the params it needs to pass them onto the PongClient
   * to set up the game.
   */
  static sptr create( Player* RemotePlayer, Player* LocalPlayer ) {
    sptr ret( new OurListener( RemotePlayer, LocalPlayer ) );
    ret->setThisPointer( ret );
    return ret;
  }

  virtual ~OurListener() {}

  void onListenFailure(const Error& error, const Address& from, const ConnectionListener::sptr& listener) {
    LockCV lock(sync);

    if (listener == connecting.lock()) {
      //Only display an error for our real player.  We don't want to see the
      //ConnectionRefused errors.
      LockObject lock( gout );
      gout << "Connection error: " << error << endl;
      gout << "  Error received from " << from << endl;
      connecting.reset();
    }

    //If waitForPlayer is waiting for the connection, wake it up.
    sync.broadcast();
  }

  void onListenSuccess( const ConnectionListener::sptr& listener ) {
    LockCV lock(sync);

    player = connecting;
    connecting.reset();
    accept = false;

    //If waitForPlayer is waiting for the connection, wake it up.
    sync.broadcast();
  }

  void getNewConnectionParams(ConnectionParams& params) {
    LockCV lock(sync);

    params.setUnrel(false);
    if (accept && connecting.expired() ) {
      //If no one is connecting and we are accepting connections
      PongClient::sptr temp = PongClient::create( remotePlayer, localPlayer );
      connecting = temp;
      params.setListener( temp );
    } else {
      params.setListener( RefuseClient::create() );
    }
  }

  //waitForPlayer returns the connected player, or NULL if the connection
  //process was aborted by the user.
  PongClient::sptr waitForPlayer() {
    LockCV lock(sync);

    //Thanks go to Peter Dimov for refactoring this code bit!
    for (;;) {
      if( PongClient::sptr p = player.lock() ) {
        return p;

      } else if( kbhit() ) {
        //We were woken up by a keypress, so refuse any further connections.
        accept = false;

        //We don't need to wait around if anyone is in the middle of connecting,
        //because shutting down GNE will close any open connections, and we will
        //be closing down if we aborted this connection.

        //Return that no client connected.
        return PongClient::sptr();

      } else {
        sync.timedWait(250);
      }
    }
  }

private:
  Player* remotePlayer;
  Player* localPlayer;

  //This variable will be non-null when there is a player, so we refuse any
  //other incoming connections.  Weak pointer used because we don't want to
  //keep player alive after connect
  PongClient::wptr player;

  //player will be stored here while he is connecting, then moved to player
  //when the connection was successful.  Weak pointer used because this
  //variable is only temporary and we don't want to keep anything alive.
  PongClient::wptr connecting;

  //If this is false, then the user canceled the connection process, we we
  //shouldn't even accept the first player.
  bool accept;

  //We use a CV because getNewConnectionParams might be called from
  //different threads, and we want to make sure only one client connects at a
  //time.  This protects the state of player.
  //The CV is notified when a new player arrives.
  ConditionVariable sync;
};
