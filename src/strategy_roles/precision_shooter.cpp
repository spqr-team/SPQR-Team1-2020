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

float tilt1 = 0;
float tilt2 = 0;
int spinner_state = 0;
bool spinner_flag = false;
unsigned long spinner_timer = 0;
float spinner_tilt = 0;
int ball_catch_state = 0;
bool ball_catch_flag = false;
unsigned long ball_catch_timer = 0;
float ball_catch_tilt = 0;

void PrecisionShooter::realPlay()
{
  if (CURRENT_DATA_READ.ballSeen)
    this->catchBall();
  else{
    ps->goCenter();
    ball_catch_flag = false;
    spinner_flag = false;
    ball_catch_state = 0;
    spinner_state = 0;
  }
}

/*
Spinning kick state machine
0: wait for the ball to be in mouth, calculate movement direction
1: tilt toward 180 deg
2: tilt back to 0 in the needed direction, stopping the roller whenn needed
*/
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
      spinner_state=1;
      spinner_flag = false;
    }
  }else if(spinner_state == 1){
    roller->speed(roller->MAX);

    int spotx;
    if(targetx > 0) spotx = targetx-PS_SPINNER_OVERHEAD;
    else spotx = targetx+PS_SPINNER_OVERHEAD;

    if(((PositionSysCamera*)ps)->isInTheVicinityOf(spotx, 0)) {

      if( !spinner_flag){
        spinner_flag = true;
        spinner_timer = millis();
      }

      if(ballPresence->isInMouth() && spinner_flag && millis() - spinner_timer > 500) {
        spinner_state=2;
        spinner_flag = false;
        spinner_tilt = CURRENT_DATA_READ.IMUAngle;
      }

      if(CURRENT_DATA_READ.posx > targetx){
        tilt1 = -0.15;
        tilt2 = 0.3;
      }else{
        tilt1 = 0.15;
        tilt2 = -0.3;
      }
    
    }else ((PositionSysCamera*)ps)->setMoveSetpoints(spotx, 0);
  }else if(spinner_state == 2){
    roller->speed(roller->MAX);

    spinner_tilt += tilt1;
    drive->prepareDrive(0,0,spinner_tilt);
    
    if(CURRENT_DATA_READ.IMUAngle > 175 && CURRENT_DATA_READ.IMUAngle < 185) {
      spinner_timer = millis();
      spinner_state=3;
    }
  }else if(spinner_state == 3){
    roller->speed(roller->MAX);
    drive->prepareDrive(0,0,spinner_tilt);
    if(millis() - spinner_timer > 1000) {
      spinner_state=4;
      spinner_tilt = CURRENT_DATA_READ.IMUAngle;
    }
  }else if(spinner_state == 4){
    spinner_tilt += tilt2;
    spinner_tilt = constrain(spinner_tilt, KICK_LIMIT_MIN, KICK_LIMIT_MAX);
    drive->prepareDrive(0,0,spinner_tilt);

    if(CURRENT_DATA_READ.IMUAngle >= KICK_LIMIT_MAX || CURRENT_DATA_READ.IMUAngle <= KICK_LIMIT_MIN) roller->speed(roller->MIN);
  }
}
/*
Ball catch state machine
0: go towards the ball, until it's been in robot's mouth for 250ms
1: slowly return facing to north (slowly otherwise we might lose the ball)
2: reach the spot
*/

void PrecisionShooter::catchBall(){

  if(ball->isInFront() && roller->roller_armed) roller->speed(roller->MAX);
  else roller->speed(roller->MIN);

  if(!ball->isInFront()){
    ball_catch_state = 0;
    ball_catch_flag = false;
  }

  if(ball_catch_state == 0){
    drive->prepareDrive(0, MAX_VEL_HALF, ballAngleFilter->calculate(CURRENT_DATA_READ.ballAngleFix));

    if(ballPresence->isInMouth() && !ball_catch_flag){
      ball_catch_flag = true;
      ball_catch_timer = millis();
    }

    if(ballPresence->isInMouth() && ball_catch_flag && millis() - ball_catch_timer > 350) {
      ball_catch_state++;
      ball_catch_tilt = CURRENT_DATA_READ.IMUAngle;
    }
  }else if(ball_catch_state == 1){
    int val = ballAngleFilter->calculate(CURRENT_DATA_READ.ballAngleFix);
    drive->prepareDrive(drive->directionAccountingForTilt(CURRENT_DATA_READ.angleAtkFix, val ),MAX_VEL_HALF,val);

    // if(ball_catch_tilt > 180) ball_catch_tilt += 0.15;
    // else if(ball_catch_tilt <= 180) ball_catch_tilt -= 0.15;

    // drive->prepareDrive(0,0,ball_catch_tilt);

    // if(CURRENT_DATA_READ.IMUAngle >= 355 || CURRENT_DATA_READ.IMUAngle <= 5) ball_catch_state = 0;
    // ((PositionSysCamera*)ps)->setMoveSetpoints(CURRENT_DATA_READ.xAtkFix, 0);
    // if(((PositionSysCamera*)ps)->isInTheVicinityOf(CURRENT_DATA_READ.xAtkFix, 0)) ball_catch_state++;
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