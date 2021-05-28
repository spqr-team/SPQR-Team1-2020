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

  gotta_tilt = false;
}

void Striker::realPlay()
{
  if (CURRENT_DATA_READ.ballSeen)
    this->striker();
  else{
    ps->goCenter();
    roller->speed(roller->MIN);
  }
}

float ctilt = 0;
unsigned long ttilt = 0;


void Striker::striker(){
  //seguo palla
  if(ball->isInFront() && roller->roller_armed) roller->speed(ROLLER_DEFAULT_SPEED);
  else roller->speed(roller->MIN);

  int ball_angle = CURRENT_DATA_READ.ballAngleFix;
  if(ball_angle > 180) ball_angle -= 360;

  if(!ball->isInMouth())ttilt=millis();

  // int tmp_ball_tilt = (0.25f*ball_angle+old_ball_Angle*0.75f);
  // ball_tilt = ball->isInMouth() ? ball_angle : ballTilt();

  // // drive->prepareDrive(0,30,ball->isInMouth() && roller->roller_armed ? tilt() : ballTilt());
  drive->prepareDrive(0,30, millis() - ttilt > 250 ? tilt():  ball_angle);

  // old_ball_Angle = ball_angle;
  // old_ball_tilt = (int) ball_tilt;
}

float Striker::ballTilt(){
  if(CURRENT_DATA_READ.ballAngle > 180 && CURRENT_DATA_READ.ballAngle < 340) ball_tilt -= 0.15f;
  else if(CURRENT_DATA_READ.ballAngle <= 180 && CURRENT_DATA_READ.ballAngle > 20) ball_tilt += 0.15f;
  return ball_tilt;
}


int Striker::tilt() {
  if(CURRENT_DATA_READ.atkSeen && (CURRENT_DATA_READ.ballAngleFix > 340 || CURRENT_DATA_READ.ballAngleFix < 20)){
    atk_tilt = roller->roller_armed ? CURRENT_DATA_READ.angleAtkFix : constrain(CURRENT_DATA_READ.angleAtkFix, -45, 45);
  }else{
    atk_tilt *= 0.8;
    if(atk_tilt <= 10) atk_tilt = 0;
  }

  return atk_tilt;
}