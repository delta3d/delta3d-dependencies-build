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
 * expong
 * It's console pong.  Over the internet.  What kind of nonsense is this?
 *
 * The expong game is a peer-to-peer game, with each client fully trusting
 * the other.  There is absolutely no checking of the scoring or movements of
 * the paddles.  This keeps the code very simple.  Also the ball's movement
 * can never be affected by another player, and this also makes the code
 * simple.  When a player misses a ball the ball still bounces off the side
 * as normal, but a notice is sent to the other side that they made a point.
 */

#include <gnelib.h>
#include <iostream>
#include <string>

using namespace std;
using namespace GNE;
using namespace GNE::Console;
using namespace GNE::PacketParser;

//Our includes have code in it.  Normally this is a bad thing, but to simplify
//the makefile process, each example in GNE only has one .cpp.
#include "packets.h"
#include "Game.h"
#include "listeners.h"

void doServer(int port);
void doClient(int port);
void doGameLoop(Game& game);
void errorExit(const char* error);
int getPort(const char* prompt);
string getName();

int main() {
  if (initGNE(NL_IP, atexit)) {
    cout << "Unable to initialize GNE" << endl;
    exit(2);
  }

  setGameInformation("GNE Pong", 1);

  if (initConsole()) {
    cout << "Unable to initialize GNE Console" << endl;
    exit(3);
  }
  setTitle("GNE Pong");

  //Register our custom packet types.  We can do this anytime after we have
  //initalized GNE, but we must do it before we start to receive packets.
  defaultRegisterPacket<PaddleMovement>();
  defaultRegisterPacket<BallMissed>();

  gout << "GNE Pong for " << GNE::VER_STR << endl;
  gout << "Local address: " << getLocalAddress() << endl;
  gout << "Type 1 for connect, 2 to wait for a player: ";
  int type;
  gin >> type;

  int port;
  if (type != 1) {
    setTitle("GNE Pong -- Server");
    gout << "Reminder: ports <= 1024 on UNIX can only be used by the superuser." << endl;
    port = getPort("listen on");
    doServer(port);
  } else {
    setTitle("GNE Pong -- Client");
    port = getPort("connect to");
    doClient(port);
  }

  return 0;
}

/**
 * The PingSender class is a little thing I just added to send PingPackets
 * every so often over a connection to do a ping counter down in the corner.
 * This code has no affect on the gameplay.
 */
class PingSender : public TimerCallback {
public:
  typedef SmartPtr<PingSender> sptr;
  typedef WeakPtr<PingSender> wptr;

protected:
  PingSender( const Connection::sptr& conn ) : conn(conn) {}

public:
  static sptr create( const Connection::sptr& conn ) {
    return sptr( new PingSender( conn ) );
  }

  void timerCallback() {
    PingPacket p;
    conn->stream().writePacket(p, true);
  }

private:
  Connection::sptr conn;
};

void doServer(int port) {
#ifdef _DEBUG
  //Generate debugging logs to server.log if in debug mode.
  initDebug(DLEVEL1 | DLEVEL2 | DLEVEL3 | DLEVEL5, "server.log");
#endif
  //We set up the players to give to the Game when we are ready to start.
  Player local(getName(), SCRX-30, SCRX-1);
  Player remote("Remote", 5, 0);

  OurListener::sptr server = OurListener::create(&remote, &local);
  if (server->open(port))
    errorExit("Cannot open server socket.");
  if (server->listen())
    errorExit("Cannot listen on server socket.");

  gout << "Server is listening on: " << server->getLocalAddress() << endl;
  gout << "Waiting for client to connect.  Press a key to abort." << endl;

  //waitForPlayer returns the connected player, or NULL if the connection
  //process was aborted by the user.  If any errors occur they will be
  //reported but listening will continue until a successful connect or the
  //user presses a key.
  PongClient::sptr remotePeer = server->waitForPlayer();

  if ( remotePeer ) {
    //Start the pingTimer to allow a ping meter
    Timer::sptr pingTimer =
      Timer::create( PingSender::create( remotePeer->getConnection() ), 500 );
    pingTimer->startTimer();

    local.paddle().setListener( remotePeer );
    //Start and play the Game.
    Game game(&local, &remote);
    doGameLoop(game);

    pingTimer->stopTimer(true);
    remotePeer->getConnection()->disconnect();
  }
}

void doClient(int port) {
#ifdef _DEBUG
  initDebug(DLEVEL1 | DLEVEL2 | DLEVEL3 | DLEVEL5, "client.log");
#endif
  string host;
  gout << "Enter hostname or IP address: ";
  gin >> host;

  Address address(host);
  address.setPort(port);
  if (!address)
    errorExit("Invalid address.");

  //Set up the game players.
  Player local(getName(), 5, 0);
  Player remote("Remote", SCRX-30, SCRX-1);

  gout << "Connecting to: " << address << endl;

  //We create a new network player tied to the remote paddle.
  PongClient::sptr peer = PongClient::create(&remote, &local);

  ClientConnection::sptr client = ClientConnection::create();

  //Open a new connection to the selected address, with no bandwidth limit
  //controls, any local bounded port, and unreliable connection is not needed.
  ConnectionParams p( peer );
  p.setUnrel(false);
  if (client->open(address, p))
    errorExit("Unable to open ClientConnection.");

  client->connect();
  client->waitForConnect();

  if (client->isConnected()) {
    //Start the pingTimer to allow a ping meter
    Timer::sptr pingTimer = Timer::create( PingSender::create(client), 500 );
    pingTimer->startTimer();

    local.paddle().setListener( peer );
    Game game(&local, &remote);
    doGameLoop(game);

    pingTimer->stopTimer(true);

  } else {
    gout << "An error occurred while connecting." << endl;
    gout << "Press a key to continue." << endl;
    getch();
  }

  //We call shutdown GNE so we know all connection active has stopped and
  //nothing is accessing our Player objects anymore.
  shutdownGNE();
}

void doGameLoop(Game& game) {
  Counter::sptr counter = Counter::create();
  Timer::sptr timer = Timer::create( counter, 40 );

  game.draw(true);

  bool exit = false;
  timer->startTimer();
  while (!exit) {
    exit = game.getInput();
    game.update();
    game.draw(false);
    //The counter will throttle the game to 25fps.
    counter->waitAndDecrement();
  }
}

void errorExit(const char* error) {
  shutdownConsole();
  cout << "Error: " << error << endl;
  exit(1);
}

int getPort(const char* prompt) {
  int port;
  gout << "Which port should we " << prompt << ": ";
  gin >> port;
  while ((port < 1) || (port > 65535)) {
    gout << "Ports range from 1 to 65535, please select one in this range: ";
    gin >> port;
  }
  return port;
}

string getName() {
  char buf[128];
  gout << "Enter your name: " << flush;
  //We use getString rather than getline because of a getline bug in the MSVC
  //DLL for MSVC 6 and earlier which reads an additional character.
  //http://support.microsoft.com/directory/article.asp?ID=KB;EN-US;Q240015&
  getString(buf, 128);
  gout << endl;
  return buf;
}
