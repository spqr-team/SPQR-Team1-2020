#include "behaviour_control/status_vector.h"
#include "systems/position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "sensors/data_source_ball.h"
#include "strategy_roles/precision_shooter.h"
#include "vars.h"
#include "math.h"


PrecisionShooter::PrecisionShooter() : Game()
{
  init();
}

PrecisionShooter::PrecisionShooter(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_)
{
  init();
}

void PrecisionShooter::init()
{
  atk_speed = 0;
  atk_direction = 0;
  atk_tilt = 0;
  cstorc = 0;

  gotta_tilt = false;
  
  ballAngleFilter = new ComplementaryFilter(0.85);
}

void PrecisionShooter::realPlay()
{
  if (CURRENT_DATA_READ.ballSeen)
    this->spinner(0);
  else
    ps->goCenter();
}

/*
Spinning kick state machine
0: wait for the ball to be in mouth, calculate movement direction
1: tilt toward 180 deg
2: tilt back to 0 in the needed direction, stopping the roller whenn needed
*/
float tilt1 = 0;
float tilt2 = 0;
int spinner_state = 0;
bool spinner_flag = false;
unsigned long spinner_timer = 0;
float spinner_tilt = 0;

void PrecisionShooter::spinner(int targetx){
  // if(!ballPresence->isInMouth()) {
  //   spinner_state=0;
  //   spinner_flag = false;
  // }

  if(spinner_state == 0){
    if(ball->isInFront() && roller->roller_armed) roller->speed(roller->MAX);

    if(ballPresence->isInMouth() && !spinner_flag){
      spinner_flag = true;
      spinner_timer = millis();
    }

    if(ballPresence->isInMouth() && spinner_flag && millis() - spinner_timer > 500) {
      spinner_state++;
      spinner_flag = false;
    }
  }else if(spinner_state == 1){
    roller->speed(roller->MAX);

    int spotx;
    if(targetx > 0) spotx = targetx-PS_SPINNER_OVERHEAD;
    else spotx = targetx+PS_SPINNER_OVERHEAD;

    if(((PositionSysCamera*)ps)->isInTheVicinityOf(spotx, 5)) {

      if( !spinner_flag){
        spinner_flag = true;
        spinner_timer = millis();
      }

      if(ballPresence->isInMouth() && spinner_flag && millis() - spinner_timer > 750) {
        spinner_state++;
        spinner_flag = false;
        spinner_tilt = CURRENT_DATA_READ.IMUAngle;
      }

      if(CURRENT_DATA_READ.posx > targetx){
        tilt1 = -0.075;
        tilt2 = 0.3;
      }else{
        tilt1 = 0.075;
        tilt2 = -0.3;
      }
    }else ((PositionSysCamera*)ps)->setMoveSetpoints(spotx, 5);
  }else if(spinner_state == 2){
    roller->speed(roller->MAX);

    spinner_tilt += tilt1;
    drive->prepareDrive(0,0,spinner_tilt);
    
    if(CURRENT_DATA_READ.IMUAngle > 175 && CURRENT_DATA_READ.IMUAngle < 185) {
      spinner_state++;
      spinner_tilt = CURRENT_DATA_READ.IMUAngle;

      spinner_timer = millis();
    }
    
  }else if(spinner_state == 3){
    roller->speed(roller->MAX);
    if(millis() - spinner_timer > 2000) spinner_state++;
  }else if(spinner_state == 4){
    spinner_tilt += tilt2;
    drive->prepareDrive(0,0,spinner_tilt);

    if(CURRENT_DATA_READ.IMUAngle > 215 || CURRENT_DATA_READ.IMUAngle < 125) roller->speed(roller->MIN);
    if(CURRENT_DATA_READ.IMUAngle > 355 || CURRENT_DATA_READ.IMUAngle < 10) spinner_state++;
  }
}
/*
Ball catch state machine
0: go towards the ball, until it's been in robot's mouth for 250ms
1: slowly return facing to north (slowly otherwise we might lose the ball)
2: reach the spot
*/
int ball_catch_state = 0;
bool ball_catch_flag = false;
unsigned long ball_catch_timer = 0;
float ball_catch_tilt = 0;

void PrecisionShooter::catchBall(){

  if(ball->isInFront() && roller->roller_armed) roller->speed(ROLLER_DEFAULT_SPEED);
  else roller->speed(roller->MIN);

  if(!ball->isInFront()){
    ball_catch_state = 0;
    ball_catch_flag = false;
  }

  if(ball_catch_state == 0){
    drive->prepareDrive(0, 30, ballAngleFilter->calculate(CURRENT_DATA_READ.ballAngleFix));

    if(ballPresence->isInMouth() && !ball_catch_flag){
      ball_catch_flag = true;
      ball_catch_timer = millis();
    }

    if(ballPresence->isInMouth() && ball_catch_flag && millis() - ball_catch_timer > 250) {
      ball_catch_state++;
      ball_catch_tilt = CURRENT_DATA_READ.IMUAngle;
    }
  }else if(ball_catch_state == 1){
    if(ball_catch_tilt > 180) ball_catch_tilt += 0.15;
    else if(ball_catch_tilt <= 180) ball_catch_tilt -= 0.15;

    if(CURRENT_DATA_READ.IMUAngle >= 355 || CURRENT_DATA_READ.IMUAngle <= 5) ball_catch_state = 0;
  }else if(ball_catch_state == 2){
    ((PositionSysCamera*)ps)->setMoveSetpoints(CURRENT_DATA_READ.xAtkFix, 0);
    if(((PositionSysCamera*)ps)->isInTheVicinityOf(CURRENT_DATA_READ.xAtkFix, 0)) ball_catch_state++;
  }
}

int PrecisionShooter::tilt() {
  if (ball->isInFront() && CURRENT_DATA_READ.ballDistance <= 90 /* || (ball->isInMouthMaxDistance() && gotta_tilt)*/ ) gotta_tilt = true;
  else gotta_tilt = false;

  if(!gotta_tilt || !CURRENT_DATA_READ.atkSeen) {
    atk_tilt *= 0.8;
    if(atk_tilt <= 10) atk_tilt = 0;
  }else{
    atk_tilt = roller->roller_armed ? CURRENT_DATA_READ.angleAtkFix : constrain(CURRENT_DATA_READ.angleAtkFix, -45, 45);
  }

  return atk_tilt;
}