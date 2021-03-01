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
    atk_speed = 0;
    atk_direction = 0;
}

void StrikerTest::realPlay(){
  if(CURRENT_DATA_READ.ballSeen) striker();
  else ps->goCenter();
}

void StrikerTest::striker()
{
  /*First implementation of "orbital striker", a new way to approach the problem with less lines.
  It works with robot's positions, calculating the final one using the angle shift over
  and over again until we have an acceptable result. That result is used to drive->prepareDrive with the speed.*/
  // if (CURRENT_DATA_READ.ballDistance > )
  //   drive->prepareDrive(CURRENT_DATA_READ.ballAngle, STRIKER_SPD);
  // else
  // {
    // if (CURRENT_DATA_READ.ballAngle > 340 && CURRENT_DATA_READ.ballAngle < 20)
    // {
    //   drive->prepareDrive(0, 100, 0);
    // }
    // else
    // {
    //   int ballAngle = (90 - CURRENT_DATA_READ.ballAngle  + 360) % 360;
    //   robotAngle = (ballAngle - 180 + 360) % 360;

    //   DEBUG.print("Ball is at angle (goniometric circle): ");
    //   DEBUG.println(ballAngle);
    //   DEBUG.print("Robot is at angle ");
    //   DEBUG.println(robotAngle);

    //   float robotAngle_rad = robotAngle*3.14 / 180;
    //   robotX = CURRENT_DATA_READ.ballDistance * cos(robotAngle_rad);
    //   robotY = CURRENT_DATA_READ.ballDistance * sin(robotAngle_rad);

    //   DEBUG.print("Coords of the robot relative to the ball: (");
    //   DEBUG.print(robotX);
    //   DEBUG.print(", ");
    //   DEBUG.print(robotY);
    //   DEBUG.println(")");

    //   // angleDiff = min(((-robotAngle + 360) % 360), ((robotAngle + 360) % 360));
    //   // angleShift = min(angleDiff, ANGLE_SHIFT_STEP);

    //   angleShift = ANGLE_SHIFT_STEP;

    //   if (robotAngle >= 0 && robotAngle <= 180)
    //     newAngle = robotAngle - angleShift;
    //   else
    //     newAngle = robotAngle + angleShift;

    //   DEBUG.print("New ball-robot angle: ");
    //   DEBUG.println(newAngle);

    //   float newAngle_rad = (newAngle)*3.14 / 180;

    //   robotX_new = TARGET_DIST * cos(newAngle_rad);
    //   robotY_new = TARGET_DIST * sin(newAngle_rad);

    //   DEBUG.print("New coords of the robot relative to the ball: (");
    //   DEBUG.print(robotX_new);
    //   DEBUG.print(", ");
    //   DEBUG.print(robotY_new);
    //   DEBUG.println(")");

    //   moveAngle = (atan2((robotX_new - robotX), (robotY_new - robotY))) * 180 / 3.14;
    //   moveAngle = (moveAngle + 360) % 360;

    //   DEBUG.print("Direction to move in: ");
    //   DEBUG.println(moveAngle);

    //   drive->prepareDrive(moveAngle, STRIKER_SPD);
    // }
  // }

  // delay(1000);
  // DEBUG.println("==========");
}



void StrikerTest::ballBack() {
}