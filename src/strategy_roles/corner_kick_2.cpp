#include "strategy_roles/corner_kick_2.h"
#include "systems/position/positionsys_camera.h"
#include "vars.h"
#include "math.h"

CornerKick2::CornerKick2() : Game() {}
CornerKick2::CornerKick2(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_) {}

void CornerKick2::init() {}

void CornerKick2::realPlay() {
  if(bt->received == 'C') {
    bt->can_send = true;
    bt->tosend = 'B';
    bt->can_send = false;

    tone(BUZZER, 320, 250);
    timer = millis();
    state=1;

    ball_catch_state = 0;
    ball_catch_tilt = 0;
    spinner_state = 0;
    spinner_tilt = 0;
    ball_catch_flag = false;
    spinner_flag = false;
  }
  if(state == 1){
    drive->prepareDrive(265, 50, 0);
    if(CURRENT_DATA_READ.bSeen && millis() - timer > 1000) {
      state ++;
      timer = millis();
    }
  }else if(state == 2){
    drive->prepareDrive(315, 50, 0);
    if(millis() - timer > 400) state++;
  }else if(state == 3){
    catchBall();
  }else if(state == 4){
    spinner(-5);
  }else if(state == 5){
    drive->prepareDrive(0,0,0);
  }
}

void CornerKick2::catchBall(){

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
    if(ball_catch_tilt > 180) ball_catch_tilt += 0.0075;
    else if(ball_catch_tilt <= 180) ball_catch_tilt -= 0.0075;

    drive->prepareDrive(0,0,ball_catch_tilt);

    if(CURRENT_DATA_READ.IMUAngle >= 355 || CURRENT_DATA_READ.IMUAngle <= 5) state++;
    // ((PositionSysCamera*)ps)->setMoveSetpoints(CURRENT_DATA_READ.xAtkFix, 0);
    // if(((PositionSysCamera*)ps)->isInTheVicinityOf(CURRENT_DATA_READ.xAtkFix, 0)) ball_catch_state++;
  }
}

void CornerKick2::spinner(int targetx){
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

    int spotx = targetx;
    // if(targetx >= 0) spotx = targetx-CK2_SPINNER_OVERHEAD;
    // else spotx = targetx+CK2_SPINNER_OVERHEAD;

    if(((PositionSysCamera*)ps)->isInTheVicinityOf(spotx, -1)) {

      if( !spinner_flag){
        spinner_flag = true;
        spinner_timer = millis();
      }

      if(ballPresence->isInMouth() && spinner_flag && millis() - spinner_timer > 500) {
        spinner_state=2;
        spinner_flag = false;
        spinner_tilt = CURRENT_DATA_READ.IMUAngle;
      }

      // if(targetx >= 0) {
        tilt1 = -0.0075;
        tilt2 = 0.55;

        limitx = 360-CK2_KICK_LIMIT_TILT1;
      // }else{
      //   tilt1 = 0.01;
      //   tilt2 = -0.55;

      //   limitx = CK2_KICK_LIMIT_TILT1;
      // }
    
    }else ((PositionSysCamera*)ps)->setMoveSetpoints(spotx, -1);
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
    // spinner_tilt = constrain(spinner_tilt, CK2_KICK_LIMIT_MIN, CK2_KICK_LIMIT_MAX);
    // drive->prepareDrive(0,0,spinner_tilt);

    if(CURRENT_DATA_READ.IMUAngle >= CK2_KICK_LIMIT_MAX || CURRENT_DATA_READ.IMUAngle <= CK2_KICK_LIMIT_MIN) {
      roller->speed(roller->MIN);
      state++;
    }
  }
}