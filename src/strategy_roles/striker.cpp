#include "behaviour_control/status_vector.h"
#include "systems/position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "sensors/data_source_ball.h"
#include "strategy_roles/striker.h"
#include "vars.h"
#include "math.h"


Striker::Striker() : Game()
{
  init();
}

Striker::Striker(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_)
{
  init();
}

void Striker::init()
{
  atk_speed = 0;
  atk_direction = 0;
  atk_tilt = 0;
  cstorc = 0;

  gotta_tilt = false;
}

void Striker::realPlay()
{
  if (CURRENT_DATA_READ.ballSeen)
    this->striker();
  else
    ps->goCenter();
}

void Striker::striker()
{
  int plusang = STRIKER_PLUSANG, ball_degrees2, dir, ball_deg = CURRENT_DATA_READ.ballAngle;

  if (CURRENT_DATA_READ.ballDistance > STRIKER_ATTACK_DISTANCE)
  {
    drive->prepareDrive(ball_deg > 180 ? CURRENT_DATA_READ.ballAngle - 20 : CURRENT_DATA_READ.ballAngle + 20, MAX_VEL_HALF, 0);
    return;
  }

  if (ball_deg > 340 || ball_deg < 20)
    plusang -= STRIKER_PLUSANG_VISIONCONE; //se ho la palla in un range di +-20 davanti, diminuisco di 20 il plus
  if (ball_deg > 180)
    ball_degrees2 = ball_deg - 360; //ragiono in +180 -180
  else
    ball_degrees2 = ball_deg;

  if (ball_degrees2 > 0)
    dir = ball_deg + plusang; //se sto nel quadrante positivo aggiungo
  else
    dir = ball_deg - plusang; //se sto nel negativo sottraggo

  if (dir < 0)
    dir = dir + 360; //se sto nel quadrante negativo ricappotto
  else
    dir = dir;

  drive->prepareDrive(dir, MAX_VEL_HALF, tilt());
}

int Striker::tilt() {
  if (ball->isInMouth() || (ball->isInMouthMaxDistance() && gotta_tilt)) gotta_tilt = true;
  else gotta_tilt = false;

  if(!gotta_tilt || !CURRENT_DATA_READ.atkSeen) {
    roller->speed(roller->MIN);
    atk_tilt *= 0.8;
    if(atk_tilt <= 10) atk_tilt = 0;
  }else{
    roller->speed(ROLLER_DEFAULT_SPEED);
    atk_tilt = constrain(CURRENT_DATA_READ.angleAtkFix, -45, 45);
  }

  return atk_tilt;

  // if (ball->isInMouth() || (ball->isInMouthMaxDistance() && gotta_tilt)) gotta_tilt = true;
  // else gotta_tilt = false;

  // if(!gotta_tilt || !CURRENT_DATA_READ.atkSeen) {
  //   roller->speed(roller->MIN);
  //   return 0;
  // }else{
  //   roller->speed(ROLLER_DEFAULT_SPEED);
  //   return constrain(CURRENT_DATA_READ.angleAtkFix, -45, 45);
  // }
}