#include <Arduino.h>
#include <gripper.h>
//#include <servo32u4.h>
#include <Romi32U4.h>
#include <LineTrackSensor.h>
#include <Distance.h>
#include <Bluemotor.h>
#include "IRdecoder.h"
#include <Chassis.h>
#include <Romi32U4Encoders.h>
#include <RemoteConstants.h>
using namespace std;

IRDecoder decoder(14);
gripper Servo1;
LineTrackSensor line;
Distance far;
Bluemotor blue;
Romi32U4Motors motors;
Chassis move;
Romi32U4Encoders encoder;

bool volUpPressed = false;
bool volPlusPressed = false;
bool moved = false;
bool leftRight = true;

void checkRemote()
{
  int16_t code = decoder.getKeyCode();
  switch (code)
  {
  case remoteVolMinus:
    volUpPressed = true;
    Servo1.operate(true);
    move.turnAngle(180);
    break;

  case remoteVolPlus:
    volPlusPressed = true;
    break;
  case remote0:
    move.pauseDriving();
    line.pause();
    break;

  case remote1:
    move.resumeDriving();
    line.resume();
    break;
  }
}

enum States
{
  setUp,
  turnAround,
  follow,
  corner,
  goBlock,
  dropOff,
  release,
  forward45,
  forward25,
  arm45,
  arm25,
  grab45,
  grab25,
  backUp,
  pickUp

} states;

void collect(int go)
{
  line.goal = 130;
  states = forward45;
  Servo1.operate(false);
  switch (states)
  {

  case forward45:
    line.follow();
    if (far.getDistance() >= 200)
    {
      states = grab45;
    }
    break;
  case grab45:
    Servo1.operate(true);

    break;
  }
}

/*
void path(int goTo)
{
  if (goTo == 0)
  {
    line.goal = 27;
    leftRight = false;
  }
  switch (states)
  {
  case setUp:
    checkRemote();
    if (volUpPressed)
    {
      states = turnAround;
      volUpPressed = false;
    }
    break;
  case (turnAround):
    if (move.doneDriving())
    {
      states = follow;
      move.pauseDriving();
      delay(1000);
    }
    break;
  case (follow):
    line.follow();
    if (line.checkStopped())
    {
      states = corner;
      delay(1000);
    }
    break;
  case (corner):
    if (move.turnLeftRight(leftRight))
    {
      states = goBlock;
    }
    break;
  case goBlock:
    line.follow();
    break;
  case dropOff:
    blue.home();
    checkRemote();
    if (volPlusPressed)
    {
      Servo1.operate();
      volPlusPressed = false;
      states = pickUp;
    }
    break;
  case pickUp:
    checkRemote();
    if (volPlusPressed)
    {
      Servo1.operate();
      volPlusPressed = false;
      states = backUp;
    }
    break;
  case backUp:
    move.turnAngle(180);
    line.follow();
    if (line.checkStopped())
    {
      move.turnAngle(90);
    }
    break;
  }
}
*/

void setup()
{
  Serial.begin(9600);
  Servo1.initilize();
  far.initilize();
  blue.initilize();
  states = setUp;
  decoder.init();
}
void loop()
{
  //blue.home();
  //collect(96);
  //blue.home();
  //blue.moveTo(3600);
  //Servo1.operate(false);
  //blue.goToRelease();
  //blue.home();

  blue.home();
  // path(0);

  //move.turnAngle(-90);
}