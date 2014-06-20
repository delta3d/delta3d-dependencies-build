#ifndef _SHARED_H_
#define _SHARED_H_

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

//This header contains the shared code between exhello and exsynchello.

void doMain(const char* connType);
void errorExit(const char* error);
int getPort(const char* prompt);
void doServer(int outRate, int inRate, int port);
void doClient(int outRate, int inRate, int port);

class OurServer;

class HelloPacket : public Packet {
public:
  typedef SmartPtr<HelloPacket> sptr;
  typedef WeakPtr<HelloPacket> wptr;

public:
  HelloPacket() : Packet(ID) {}
  //copy ctor not needed
  HelloPacket(string message2) : Packet(MIN_USER_ID), message(message2) {}

  virtual ~HelloPacket() {}

  static const int ID;

  int getSize() const {
    return Packet::getSize() + Buffer::getSizeOf(message);
  }

  void writePacket(Buffer& raw) const {
    Packet::writePacket(raw);
    raw << message;
  }

  void readPacket(Buffer& raw) {
    Packet::readPacket(raw);
    raw >> message;
  }

  string getMessage() {
    return message;
  }

private:
  string message;
};

const int HelloPacket::ID = MIN_USER_ID;

class OurListener : public ServerConnectionListener {
protected:
  OurListener(int iRate, int oRate) 
    : ServerConnectionListener(), iRate(iRate), oRate(oRate) {
  }

public:
  typedef SmartPtr<OurListener> sptr;
  typedef WeakPtr<OurListener> wptr;

  static sptr create(int iRate, int oRate) {
    sptr ret( new OurListener( iRate, oRate ) );
    ret->setThisPointer( ret );
    return ret;
  }

  virtual ~OurListener() {}

  void onListenFailure(const Error& error, const Address& from, const ConnectionListener::sptr& listener) {
    mprintf("Connection error: %s\n", error.toString().c_str());
    mprintf("  Error received from %s\n", from.toString().c_str());
  }

  void getNewConnectionParams(ConnectionParams& params);

private:
  int iRate;
  int oRate;
};

void errorExit(const char* error) {
  gout << "Fatal Error: " << error << endl;
  gout << " Press a key." << endl;
  getch();
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

void doMain(const char* connType) {
  if (initGNE(NL_IP, atexit)) {
    exit(1);
  }

  //sets our game info, used in the connection process by GNE to error check.
  //We give exhello and exsynchello the same name because they are compatable
  //with each other.
  setGameInformation("hello examples", 1);

  initConsole();
  setTitle("GNE Basic Connections Example");

  //register HelloPacket using default behavior and allocators.
  defaultRegisterPacket<HelloPacket>();

  gout << "GNE " << connType << " Basic Connections Example for " << GNE::VER_STR << endl;
  gout << "Local address: " << getLocalAddress() << endl;
  gout << "Should we act as the server, or the client?" << endl;
  gout << "Type 1 for client, 2 for server: ";
  int type;
  gin >> type;

  int port;
  if (type == 2) {
    setTitle("GNE Basic Connections Example -- Server");
    gout << "Reminder: ports <= 1024 on UNIX can only be used by the superuser." << endl;
    port = getPort("listen on");
    doServer(0, 0, port);
  } else {
    setTitle("GNE Basic Connections Example -- Client");
    port = getPort("connect to");
    doClient(0, 0, port);

    gout << "Press a key to continue." << endl;
    getch();
  }
}

//For both types of exhello, starting the server is the same.
void doServer(int outRate, int inRate, int port) {
#ifdef _DEBUG
  //Generate debugging logs to server.log if in debug mode.
  initDebug(DLEVEL1 | DLEVEL2 | DLEVEL3 | DLEVEL4 | DLEVEL5, "server.log");
#endif

  OurListener::sptr server = OurListener::create(inRate, outRate);
  if (server->open(port))
    errorExit("Cannot open server socket.");
  if (server->listen())
    errorExit("Cannot listen on server socket.");

  gout << "Server is listening on: " << server->getLocalAddress() << endl;
  gout << "Press a key to shutdown server." << endl;
  getch();

  //This is not strictly needed, all listeners will be shutdown when GNE
  //shuts down.
  server->close();
}

#endif
