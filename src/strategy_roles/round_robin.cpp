#include "behaviour_control/status_vector.h"
#include "systems/position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "sensors/data_source_ball.h"
#include "strategy_roles/round_robin.h"
#include "vars.h"
#include "math.h"


RoundRobin::RoundRobin() : Game()
{
  init();
}

RoundRobin::RoundRobin(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_)
{
  init();
}

void RoundRobin::init()
{
  atk_speed = 0;
  atk_direction = 0;
  atk_tilt = 0;
  cstorc = 0;

  gotta_tilt = false;
  
  ballAngleFilter = new ComplementaryFilter(0.1);
}

void RoundRobin::realPlay()
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
void RoundRobin::spinner(int targetx){
  // if(!ballPresence->isInMouth()) {
  //   spinner_state=0;
  //   spinner_flag = false;
  // }

  if(spinner_state == 0){
    if(ball->isInFront() && roller->roller_armed) roller->speed(roller->MAX-200);

    if(ballPresence->isInMouth() && !spinner_flag){
      spinner_flag = true;
      spinner_timer = millis();
    }
    if(ballPresence->isInMouth() && spinner_flag && millis() - spinner_timer > 100) {
      spinner_state=1;
      spinner_flag = false;
    }
  }else if(spinner_state == 1){
    roller->speed(roller->MAX);

    int spotx = targetx;
    if(targetx >= 0) spotx = targetx-RR_SPINNER_OVERHEAD;
    else spotx = targetx+RR_SPINNER_OVERHEAD;

    if(((PositionSysCamera*)ps)->isInTheVicinityOf(spotx, RR_YCOORD)) {
      // if( !spinner_flag){
      //   spinner_flag = true;
      //   spinner_timer = millis();
      // }

      // if(ballPresence->isInMouth() && spinner_flag && millis() - spinner_timer > 500) {
        spinner_state=2;
        spinner_flag = false;
        spinner_tilt = CURRENT_DATA_READ.IMUAngle;
      // }

      if(targetx >= 0) {
        tilt1 = -0.15;
        tilt2 = -1.55;
        limitx = RR_KICK_LIMIT_TILT1;

      }else{
        tilt1 = 0.15;
        tilt2 = 1.55;        limitx = 360-RR_KICK_LIMIT_TILT1;


      }
    
    }else ((PositionSysCamera*)ps)->setMoveSetpoints(spotx, RR_YCOORD);

  }else if(spinner_state == 2){
    roller->speed(RR_ROLLER_SPD);

    spinner_tilt += tilt1;
    drive->prepareDrive(0,0,spinner_tilt);
    
    if(CURRENT_DATA_READ.IMUAngle > limitx-5 && CURRENT_DATA_READ.IMUAngle < limitx+5) {
      spinner_timer = millis();
      spinner_state=3;
    }
  }else if(spinner_state == 3){
    roller->speed(RR_ROLLER_SPD);
    drive->prepareDrive(0,0,spinner_tilt);
    if(millis() - spinner_timer > 150) {
      spinner_state=4;
      spinner_tilt = CURRENT_DATA_READ.IMUAngle;
    }
  }else if(spinner_state == 4){
    // drive->prepareDrive(0,0,0);

    spinner_tilt += tilt2;
    spinner_tilt = constrain(spinner_tilt, RR_KICK_LIMIT_MIN, RR_KICK_LIMIT_MAX);
    drive->prepareDrive(0,0,spinner_tilt);

    if(CURRENT_DATA_READ.IMUAngle >= RR_KICK_LIMIT_MAX || CURRENT_DATA_READ.IMUAngle <= RR_KICK_LIMIT_MIN) {
      roller->speed(roller->MIN);
      spinner_tilt = 0;
    }
  }
}
/*
Ball catch state machine
0: go towards the ball, until it's been in robot's mouth for 250ms
1: slowly return facing to north (slowly otherwise we might lose the ball)
2: reach the spot
*/

void RoundRobin::catchBall(){

  if(!ball->isInFront()){
    ball_catch_state = 0;
    ball_catch_flag = false;
    ball_catch_tilt = 0;
  }

  if(ball_catch_state == 0){

    if(ball->isInFront() && roller->roller_armed) roller->speed(roller->MAX);
    else roller->speed(roller->MIN);

    drive->prepareDrive(0, ROUND_ROBIN_VEL, ballAngleFilter->calculate(CURRENT_DATA_READ.ballAngleFix));

    if(ballPresence->isInMouth() && !ball_catch_flag){
      ball_catch_flag = true;
      ball_catch_timer = millis();
    }

    if(ballPresence->isInMouth() && ball_catch_flag && millis() - ball_catch_timer > 50) {
      ball_catch_state++;
      ball_catch_tilt = CURRENT_DATA_READ.IMUAngle;
    }
  }else if(ball_catch_state == 1){
    if(ball_catch_tilt > 180 && ball_catch_tilt < 360) ball_catch_tilt += 0.15;
    else if(ball_catch_tilt <= 180 && ball_catch_tilt > 0) ball_catch_tilt -= 0.15;

    drive->prepareDrive(0,0,ball_catch_tilt);

    if(CURRENT_DATA_READ.IMUAngle >= 350 || CURRENT_DATA_READ.IMUAngle <= 5) ball_catch_state = 2;
  }else if(ball_catch_state == 2){
    spinner_tilt = 0;
    spinner_flag = false;
    spinner_timer = 0;
    spinner_state = 1;
    ball_catch_state = 3;
  }else if(ball_catch_state == 3){
    this->spinner(28);
  }
}
