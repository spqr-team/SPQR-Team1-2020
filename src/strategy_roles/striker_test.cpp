#include <Arduino.h>

#include "behaviour_control/status_vector.h"
#include "sensors/sensors.h"
#include "strategy_roles/striker_test.h"
#include "vars.h"

#include "math.h"

StrikerTest::StrikerTest() : Game() {
  init();
}

StrikerTest::StrikerTest(LineSystem* ls_, PositionSystem* ps_) : Game(ls_, ps_) {
  init();
}

void StrikerTest::init(){
  robotAngle = 0;
  robotX = 0;
  robotX_new = 0;
  robotY = 0;
  robotY_new = 0;
  angleShift = 0;
  angleDiff = 0;
  moveAngle = 0;
}

void StrikerTest::realPlay(){
  if(CURRENT_DATA_READ.ballSeen) striker();
  else ps->goCenter();
}

void StrikerTest::striker() {
/*First implementation of "orbital striker", a new way to approach the problem with less lines.
  It works with robot's positions, calculating the final one using the angle shift over
  and over again until we have an acceptable result. That result is used to drive->prepareDrive with the speed.*/
  if (CURRENT_DATA_READ.ballAngle >= 350 && CURRENT_DATA_READ.ballAngle <= 10) 
    drive->prepareDrive(CURRENT_DATA_READ.ballAngle, STRIKER_SPD);
  robotAngle = -90 + ((CURRENT_DATA_READ.ballAngle + 180) % 360);
  robotX = CURRENT_DATA_READ.ballDistance * cos(robotAngle);
  robotY = CURRENT_DATA_READ.ballDistance * sin(robotAngle);
  angleDiff = min(((- robotAngle + 360) % 360), ((robotAngle + 360) % 360));
  angleShift = min(angleDiff, ANGLE_SHIFT_STEP);
  if (robotAngle >= 0 && robotAngle <= 180) newAngle = robotAngle + angleShift;
  else newAngle = robotAngle - angleShift;
  robotX_new = TARGET_DIST - cos(newAngle);
  robotY_new = TARGET_DIST - sin(newAngle);
  moveAngle = atan2((robotX - robotX_new),(robotY - robotY_new));
  moveAngle += 90;
  drive->prepareDrive(moveAngle, STRIKER_SPD);
}



void StrikerTest::ballBack() {
}