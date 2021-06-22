#include "behaviour_control/status_vector.h"
#include "systems/position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "sensors/data_source_ball.h"
#include "strategy_roles/striker_roller.h"
#include "vars.h"
#include "math.h"


StrikerRoller::StrikerRoller() : Game()
{
  init();
}

StrikerRoller::StrikerRoller(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_)
{
  init();
}

void StrikerRoller::init()
{
  atk_speed = 0;
  atk_direction = 0;
  atk_tilt = 0;
  cstorc = 0;

  gotta_tilt = false;
  
  ballAngleFilter = new ComplementaryFilter(0.85);
}

void StrikerRoller::realPlay()
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
void StrikerRoller::spinner(int targetx){
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

    if(ballPresence->isInMouth() && spinner_flag && millis() - spinner_timer > 50) {
      spinner_state=1;
      spinner_flag = false;
    }
  }else if(spinner_state == 1){
    roller->speed(roller->MAX);

    spinner_state=2;
    spinner_flag = false;
    spinner_tilt = CURRENT_DATA_READ.IMUAngle;

    if(CURRENT_DATA_READ.posx < targetx) {
      tilt1 = -0.15;
      tilt2 = 0.55;

      limitx = 360-STRL_KICK_LIMIT_TILT1;
    }else{
      tilt1 = 0.15;
      tilt2 = -0.55;

      limitx = STRL_KICK_LIMIT_TILT1;
    }
  }else if(spinner_state == 2){
    roller->speed(roller->MAX);

    spinner_tilt += tilt1;
    drive->prepareDrive(0,0,spinner_tilt);
    
    if(CURRENT_DATA_READ.IMUAngle > limitx-5 && CURRENT_DATA_READ.IMUAngle < limitx+5) {
      spinner_timer = millis();
      spinner_state=3;
    }
  }else if(spinner_state == 3){
    roller->speed(roller->MAX);
    drive->prepareDrive(0,0,spinner_tilt);
    if(millis() - spinner_timer > 150) {
      spinner_state=4;
      spinner_tilt = CURRENT_DATA_READ.IMUAngle;
    }
  }else if(spinner_state == 4){
    drive->prepareDrive(0,0,0);

    // spinner_tilt += tilt2;
    // spinner_tilt = constrain(spinner_tilt, KICK_LIMIT_MIN, KICK_LIMIT_MAX);
    // drive->prepareDrive(0,0,spinner_tilt);

    if(CURRENT_DATA_READ.IMUAngle >= STRL_KICK_LIMIT_MAX || CURRENT_DATA_READ.IMUAngle <= STRL_KICK_LIMIT_MAX) roller->speed(roller->MIN);
  }
}
/*
Ball catch state machine
0: go towards the ball, until it's been in robot's mouth for 250ms
1: slowly return facing to north (slowly otherwise we might lose the ball)
2: reach the spot
*/

void StrikerRoller::catchBall(){

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

    if(ballPresence->isInMouth() && ball_catch_flag && millis() - ball_catch_timer > 50) {
      ball_catch_state++;
    }
  }else if(ball_catch_state == 1){
    int val = ballAngleFilter->calculate(CURRENT_DATA_READ.ballAngleFix);
    // val = val > 10 || val < 10 ? val : 0;

    drive->prepareDrive(drive->directionAccountingForTilt(CURRENT_DATA_READ.angleAtkFix, val ),MAX_VEL_HALF,val);

    if(CURRENT_DATA_READ.distAtk <= 25){
       ball_catch_state++;
       spinner_state = 0;
       spinner_flag = false;
       spinner_tilt = 0;
      //  drive->prepareDrive(0,0,0);
    }
  }else if(ball_catch_state == 2){
    spinner(0);
  }
}

int StrikerRoller::tilt() {
  if (ball->isInFront() && CURRENT_DATA_READ.ballDistance <= 90 /* || (ball->isInMouthMaxDistance() && gotta_tilt)*/ ) gotta_tilt = true;
  else gotta_tilt = false;

  if(!gotta_tilt || !CURRENT_DATA_READ.atkSeen) {
    atk_tilt = roller->roller_armed ? CURRENT_DATA_READ.angleAtkFix : constrain(CURRENT_DATA_READ.angleAtkFix, -45, 45);
  }

  return atk_tilt;
}