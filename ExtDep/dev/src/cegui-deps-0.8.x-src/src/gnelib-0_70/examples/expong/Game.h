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

//This code contains all of the game logic, completely separate of the
//networking code.

const int SCRX     = 80;
const int SCRY     = 24;
const int SCRX_MID = SCRX / 2;
const int SCRY_MID = SCRY / 2;

/**
 * The Ball class represents the pong ball.
 */
class Ball {
public:
  Ball() : oldx(SCRX_MID), oldy(SCRY_MID),
           x((float)SCRX_MID), y((float)SCRY_MID),
           dx(1.0), dy(0.5) {
  }

  //The update function for the ball returns a y position if a collision with
  //the local side occured, else it returns -1.
  int update(bool isLocalLeft) {
    int ret = -1;

    //The temp old variables are so we can undo our actions if they will lead
    //to a collision.
    float tempOldX = x;
    float tempOldY = y;
    x += dx;
    y += dy;

    //Now check for collisions.
    //Check for side collision
    if (x < 1.0) {
      dx = -dx;
      x = tempOldX;
      if (isLocalLeft)  //If we collided with the local side, return the y
        ret = (int)y;   // value so we can detect if there was a collision.

    } else if (x >= SCRX-1) {
      dx = -dx;
      x = tempOldX;
      if (!isLocalLeft) //If we collided with the local side, return the y
        ret = (int)y;   // value so we can detect if there was a collision.
    }

    //Check for vertical collision
    if (y < 1.0 || y >= SCRY-1) {
      dy = -dy;
      y = tempOldY;
    }

    return ret;
  }

  void draw(bool redraw) {
    //Erase old ball and draw new one.
    mlprintf(oldx, oldy, " ");

    //Draw a high or low block depending on the y value.
    if ((int)y == y)
      mlputchar((int)x, (int)y, 223);
    else
      mlputchar((int)x, (int)y, 220);

    oldx = (int)x;
    oldy = (int)y;
  }

private:
  int oldx, oldy;
  float x, y;
  float dx, dy;
};

/**
 * The PaddleListener class allows the networking code to register itself as
 * a listener of a paddle so that it can be notified of changes in the game's
 * state, so that it may replicate it to the remote machine.
 */
class PaddleListener {
public:
  typedef SmartPtr<PaddleListener> sptr;
  typedef WeakPtr<PaddleListener> wptr;

public:
  virtual void paddleMoved(int newy) = 0;

  virtual void ballMissed() = 0;
};

const int PADDLE_HEIGHT = 5;

/**
 * The paddle class represents the player in the game.  It has some
 * functionality so that it can communicate with the networking code.  The
 * rest of the game logic does not.
 */
class Paddle {
public:
  Paddle(int x2) : oldy(10), x(x2), y(10) {
  }

  //The networking code will call this function when we get a PacketMovement.
  void changePosition(int newy) {
    //We have to change y in the sync to make sure that we don't change it
    //as the game thread is accessing it.
    LockMutex lock(sync);
    y = newy;
  }

  /**
   * The networking code will call this function when a connection is made to
   * set itself up as a listener.
   */
  void setListener( const PaddleListener::sptr& newListener ) {
    LockMutex lock( sync );

    //gnedbgo1(1, "%x is now our listener", newListener);
    listener = newListener;
  }

  /**
   * Returns true if this paddle is on the left side.
   */
  bool isLeftSide() {
    return (x < SCRX_MID);
  }

  /**
   * Checks to see if the y coordinate hit the paddle or not.  If it missed,
   * then it sends a ballMissed event to its listener.  Returns true if a
   * point was scored.
   */
  bool checkCollision(int chk) {
    LockMutex lock( sync );

    if (listener) {
      //Only do the check if we have a listener to notify anyways.
      if (chk < y || chk >= y + PADDLE_HEIGHT) {
        listener->ballMissed();
        return true;
      }
    }

    return false;
  }

  void getInput(char ch) {
    LockMutex lock( sync );

    switch (ch) {
    case 'w':
      //If the paddle can move up, we move up a space
      if (y > 1) {
        --y;
        //Notify our listener that we have moved, if we have one.
        if (listener)
          listener->paddleMoved(y);
      }
      break;

    case 's':
      //If the paddle can move down, we move down a space
      if (y < SCRY - 1 - PADDLE_HEIGHT) {
        ++y;
        //Notify our listener that we have moved, if we have one.
        if (listener)
          listener->paddleMoved(y);
      }
      break;
    }
  }

  void update() {
  }

  void draw(bool redraw) {
    LockMutex lock( sync );

    //Only draw the paddle if it has moved, or we need to redraw
    if (oldy != y || redraw) {
      int c = 0;
      //Erase old paddle
      for (c=0; c<PADDLE_HEIGHT; ++c) {
        mlputchar(x, oldy+c, ' ');
      }
      //Draw new paddle
      for (c=0; c<PADDLE_HEIGHT; ++c) {
        mlputchar(x, y+c, '|');
      }
      
      oldy = y;
    }
  }

private:
  PaddleListener::sptr listener;

  int oldy;
  int x, y;

  //We have to provide a mutex, because the networking code can change our
  //position at any time, if we are being controlled by the network.  If the
  //y position was changed in the middle of a draw, Bad Things would happen.
  //So anytime we access y we will acquire this mutex to allow only one
  //thread at a time into that area of code.
  Mutex sync;
};

/**
 * This class is 100% pure fluff and has nothing to do with the gameplay or
 * using GNE, but it does let you know when you get a point...
 */
class TextAnim {
public:
  TextAnim() : currMode(OFF) {}

  void displayMessage(string newMsg, int loc) {
    msg = newMsg;
    x = loc;
    currChar = 0;
    currMode = DRAW;
    //We set inc to false because we don't know if we will get a draw or an
    //update next, and this will help make sure we don't skip the first char.
    inc = false;
  }

  void update() {
    if (currMode != OFF) {
      //The inc is used to update every other frame, to slow down the anim
      //a little bit.
      if (inc) {
        ++currChar;
        if ((std::string::size_type)currChar >= msg.size()) {
          currChar = 0;
          
          if (currMode == DRAW)
            currMode = ERASE;
          else
            currMode = OFF;
        }
        inc = false;

      } else
        inc = true;
    }
  }

  void draw(bool redraw) {
    if (currMode != OFF) {
      int ch = '=';
      
      if (currMode == DRAW)
        ch = msg[currChar];
      
      mlputchar(x+currChar, SCRY-1, ch);
    }
  }

private:
  enum AnimMode {
    OFF,
    DRAW,
    ERASE
  };

  AnimMode currMode;

  bool inc;

  string msg;

  int x;
  int currChar;
};

class Player {
public:
  Player(string playerName, int displayX, int paddleX)
    : x(displayX), name(playerName), updateScore(false), score(0),
    ourPaddle(paddleX) {
  }

  void setName(string newName) {
    name = newName;
  }

  const string& getName() const {
    return name;
  }

  void getInput(char ch) {
    ourPaddle.getInput(ch);
  }

  void update() {
    ourPaddle.update();

    LockMutex lock( sync );
    anim.update();
  }

  void draw(bool redraw) {
    LockMutex lock( sync );

    if (updateScore || redraw) {
      mlprintf(x, 0, " %s %2d ", name.c_str(), score);
      updateScore = false;
    }
    anim.draw(redraw);

    ourPaddle.draw(redraw);
  }

  void incrementScore() {
    LockMutex lock( sync );

    ++score;
    updateScore = true;
    anim.displayMessage(" " + name + " scores! ", x);
  }

  Paddle& paddle() {
    return ourPaddle;
  }

private:
  //This is the screen location on the first row where we output our
  //name and score
  int x;
  //This is the player's name
  string name;

  //updateScore is true if the score has changed and needs drawing.
  bool updateScore;
  int score;

  Paddle ourPaddle;

  //Provides a mutex to guard the score and updateScore variables.
  //It also protects the TextAnim instance.
  Mutex sync;

  //This is just for fluff when someone scores.
  TextAnim anim;
};

class Game {
public:
  /**
   * The Game class takes the paddles that were set up from the network
   * connection process.
   */
  Game(Player* Local, Player* Remote) : local(Local), remote(Remote) {
  }

  bool getInput() {
    while (kbhit()) {
      //Get a key if one is available
      int ch = getch();
      //We quit with q, else we pass it to the paddle
      if (ch == 'q')
        return true;
      else
        local->getInput((char)ch);
    }
    return false;
  }

  void update() {
    local->update();
    remote->update();

    int temp = ball.update( local->paddle().isLeftSide() );
    if (temp >= 0) {
      //The the ball hit the paddle ends.  Check for collision.  We only have
      //do this for the local paddle.  The remote machine would send a packet
      //if the remote end missed.
      if (local->paddle().checkCollision(temp))
        remote->incrementScore();
    }
  }

  //If redraw is true, then we assume the screen needs total updating (this
  //is true for the first draw).
  void draw(bool redraw) {

    if (redraw) {
      //Draw the board
      for (int x=0; x<SCRX; ++x) {
        //Draw top rail
        mlputchar(x, 0, '=');

        //The middle loop clears out any text in the middle.
        for (int y=1; y<SCRY-1; ++y)
          mlputchar(x, y, ' ');

        //Draw bottom rail
        mlputchar(x, SCRY-1, '=');
      }
    }

    local->draw(redraw);
    remote->draw(redraw);
    ball.draw(redraw);
  }

private:
  Player* local;
  Player* remote;

  Ball ball;
};
