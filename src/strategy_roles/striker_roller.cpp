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
  
  ballAngleFilter = new ComplementaryFilter(0);
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
    
    // decide with direction to rotate
    spinner_tilt = CURRENT_DATA_READ.IMUAngle;

    if(CURRENT_DATA_READ.angleAtk >= 0) {
        tilt1 = -0.25;
        tilt2 = 5;
        limitx = 360-STRL_KICK_LIMIT_TILT1;
      }else{
        tilt1 = 0.25;
        tilt2 = -5;
        limitx = STRL_KICK_LIMIT_TILT1;
      }
    // if(CURRENT_DATA_READ.posx >= -5 && CURRENT_DATA_READ.posx <= 5){
    //   if(CURRENT_DATA_READ.IMUAngle >= 180) {
    //     tilt1 = -0.25;
    //     tilt2 = 15;
    //     limitx = 360-STRL_KICK_LIMIT_TILT1;
    //   }else{
    //     tilt1 = 0.25;
    //     tilt2 = -15;
    //     limitx = STRL_KICK_LIMIT_TILT1;
    //   }
    // }else if(CURRENT_DATA_READ.posx < -5){
    //     tilt1 = 0.25;
    //     tilt2 = -5;
    //     limitx = STRL_KICK_LIMIT_TILT1;
    // }else if(CURRENT_DATA_READ.posx > 5){
    //     tilt1 = -0.25;
    //     tilt2 = 5;
    //     limitx = 360-STRL_KICK_LIMIT_TILT1;
    // }
    // if(CURRENT_DATA_READ.IMUAngle < limitx) tilt1 *= -1; //we need to invert the rotatiion if we are on the opposite side

  }else if(spinner_state == 2){
    roller->speed(roller->MAX);

    spinner_tilt = spinner_tilt + tilt1;
    // This ensures no strange rotation happens
    if(spinner_tilt <= -360) spinner_tilt+=360;
    if(spinner_tilt >= 360) spinner_tilt -= 360;

    drive->prepareDrive(0,0,spinner_tilt);
    
    if(CURRENT_DATA_READ.IMUAngle > limitx-5 && CURRENT_DATA_READ.IMUAngle < limitx+5) {
      spinner_state=3;
      spinner_tilt = CURRENT_DATA_READ.IMUAngle;
    }
  }else if(spinner_state == 3){
    roller->speed(roller->MAX);
    // stay there a little bit
    drive->prepareDrive(0,0,spinner_tilt);

    if(millis() - spinner_timer > 150) {
      spinner_state=4;
      spinner_tilt = CURRENT_DATA_READ.IMUAngle;
    }
  }else if(spinner_state == 4){
    // fast return which gives momentum to the ball
    drive->prepareDrive(0,0,spinner_tilt);

    spinner_tilt += tilt2;
    spinner_tilt = constrain(spinner_tilt, 5, 355);

    // turn roller off and kick
    if(CURRENT_DATA_READ.IMUAngle >= STRL_KICK_LIMIT_MAX || CURRENT_DATA_READ.IMUAngle <= STRL_KICK_LIMIT_MAX) {
      roller->speed(roller->MIN);
      if(!spinner_end_flag){
        spinner_end_time = millis();
        spinner_end_flag = true;
      }
    }
    // if(ballPresence->isInMouth()) {
    //   spinner_state = 1;
    //   spinner_flag = false; 
    // }
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

  // if(!ball->isInFront() && millis() - spinner_end_time > 500 && spinner_end_flag){
  //   ball_catch_state = 0;
  //   ball_catch_flag = false;
  //   spinner_end_flag = false;
  // }
  if(!ball->isInFront()){
    ball_catch_state = 0;
    ball_catch_flag = false;
  }

  if(ball_catch_state == 0){
    // tilt torwards the ball until it's in the mouth
    drive->prepareDrive(0, MAX_VEL_HALF, ballAngleFilter->calculate(CURRENT_DATA_READ.ballAngleFix));

    if(ballPresence->isInMouth() && !ball_catch_flag){
      ball_catch_flag = true;
      ball_catch_timer = millis();
    }

    if(ballPresence->isInMouth() && ball_catch_flag && millis() - ball_catch_timer > 50) {
      ball_catch_state++;
    }
  }else if(ball_catch_state == 1){
    // go towards the goal without resetting tilt
    // this makes it so that the robot sometimes walks backwards, hiding the ball from any opponent
    // a spinning kick is the only way to free the ball here
    int val = ballAngleFilter->calculate(CURRENT_DATA_READ.ballAngleFix);

    drive->prepareDrive(drive->directionAccountingForTilt(CURRENT_DATA_READ.angleAtkFix, val ),MAX_VEL_HALF,val);

    if(CURRENT_DATA_READ.distAtk <= 26){
      //  ball_catch_state++;
      //  spinner_state = 0;
      //  spinner_flag = false;
      //  spinner_tilt = CURRENT_DATA_READ.IMUAngle;

      drive->prepareDrive(0,0,0);
      if(CURRENT_DATA_READ.IMUAngle >= STRL_KICK_LIMIT_MAX || CURRENT_DATA_READ.IMUAngle <= STRL_KICK_LIMIT_MAX) roller->speed(roller->MIN);
    }
  }else if(ball_catch_state == 2){
    // Spinny kick
    
    // spinner(0);
    if(CURRENT_DATA_READ.angleAtkFix >= 0) {
      tilt2 = 3;
    }else{
      tilt2 = -3;
    }

    drive->prepareDrive(0,0,spinner_tilt);

    spinner_tilt += tilt2;
    spinner_tilt = constrain(spinner_tilt, 5, 355);

    // turn roller off and kick
    if(CURRENT_DATA_READ.IMUAngle >= STRL_KICK_LIMIT_MAX || CURRENT_DATA_READ.IMUAngle <= STRL_KICK_LIMIT_MAX) {
      roller->speed(roller->MIN);
      if(!spinner_end_flag){
        spinner_end_time = millis();
        spinner_end_flag = true;
      }
    }
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