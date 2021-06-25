#include "behaviour_control/status_vector.h"
#include "systems/position/positionsys_camera.h"
#include "systems/lines/linesys_camera_roundrobin.h"
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
    // this->spinner(0);
    // this->push();
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
    if(targetx >= 0) spotx = targetx-RR_SPINNER_OVERHEAD;
    else spotx = targetx+RR_SPINNER_OVERHEAD;

    // if(((PositionSysCamera*)ps)->isInTheVicinityOf(spotx, 0)) {

    //   if( !spinner_flag){
    //     spinner_flag = true;
    //     spinner_timer = millis();
    //   }

    //   if(ballPresence->isInMouth() && spinner_flag && millis() - spinner_timer > 500) {
        spinner_state=2;
    //     spinner_flag = false;
    //     spinner_tilt = CURRENT_DATA_READ.IMUAngle;
    //   }

    //   if(targetx >= 0) {
        tilt1 = -0.15;
        tilt2 = -35;

        limitx = 360-RR_KICK_LIMIT_TILT1;
    //   }else{
    //     tilt1 = 0.15;
    //     tilt2 = -0.55;

    //     limitx = RR_KICK_LIMIT_TILT1;
    //   }
    
    // }else ((PositionSysCamera*)ps)->setMoveSetpoints(spotx, 0);
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
    // drive->prepareDrive(0,0,0);
    spinner_tilt += tilt2;
    spinner_tilt = constrain(spinner_tilt, RR_KICK_LIMIT_MIN, RR_KICK_LIMIT_MAX);
    drive->prepareDrive(0,0,spinner_tilt);

    if(CURRENT_DATA_READ.IMUAngle >= RR_KICK_LIMIT_MAX || CURRENT_DATA_READ.IMUAngle <= RR_KICK_LIMIT_MIN) {
    ball_catch_state++;

    roller->speed(roller->MIN);
    }
  }
}


void RoundRobin::spinnerStep(){
  spinner_state++;
  spinner_timer = millis();
}

/*void RoundRobin::push(){
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

    if(((PositionSysCamera*)ps)->isInRoughVicinityOf(0, -6)) spinner_state=4;
    else ((PositionSysCamera*)ps)->setMoveSetpoints(0, -6);
  // } else if(spinner_state == 2){
  //   roller->speed(roller->MAX);
  //   if(((PositionSysCamera*)ps)->isInTheVicinityOf(16, -4)) spinnerStep();
  //   else ((PositionSysCamera*)ps)->setMoveSetpoints(16, -4);
  // }else if(spinner_state == 3){
  //   drive->prepareDrive(0,0,0);
  //   if(millis() - spinner_timer > 750) spinnerStep();
  }else if(spinner_state == 4){
    drive->prepareDrive(45, 50, 0);
    if( ((LineSysCameraRR*)ls)->tookLine ) spinnerStep();
  }else if(spinner_state == 5){
    roller->speed(roller->MIN);
    if(millis()-spinner_timer > 1500) spinnerStep();
  }else if(spinner_state == 6){
    drive->prepareDrive(180, 30, 0);
    if(millis() - spinner_timer > 750) spinnerStep();
  }else if(spinner_state == 7){
    roller->speed(roller->MIN);
    drive->prepareDrive(0, 0, 55);
    if(millis() - spinner_timer > 1000) spinnerStep();
  }else if(spinner_state == 8){
    drive->prepareDrive(drive->directionAccountingForTilt(0, 55), 100, 55);
    if(millis() - spinner_timer > 500) spinnerStep();
  }else if(spinner_state == 9){
    drive->prepareDrive(drive->directionAccountingForTilt(180, 55), 50, 55);
    if(millis() - spinner_timer > 750) spinnerStep();
  }else if(spinner_state == 10){
    if(((PositionSysCamera*)ps)->isInRoughVicinityOf(0, -8)) spinnerStep();
    else ((PositionSysCamera*)ps)->setMoveSetpoints(0, -8);
  }else ball_catch_state++;
}*/
void RoundRobin::push(){
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

    // if(flip)
    //   if(CURRENT_DATA_READ.yDist <= 24) drive->prepareDrive(0, 50, 0);
    //   if(CURRENT_DATA_READ.yDist >= 36)  drive->prepareDrive(180, 50, 0);
    // else{
    //   if(CURRENT_DATA_READ.bDist <= 24) drive->prepareDrive(0, 50, 0);
    //   if(CURRENT_DATA_READ.bDist >= 36)  drive->prepareDrive(180, 50, 0);
    // }

    if(flip==0){
    if(((PositionSysCamera*)ps)->isInRoughVicinityOf(0, -3)) spinnerStep();
    else ((PositionSysCamera*)ps)->setMoveSetpoints(0, -3);
    }else{
    if(((PositionSysCamera*)ps)->isInRoughVicinityOf(0, -12)) spinnerStep();
    else ((PositionSysCamera*)ps)->setMoveSetpoints(0, -12);
    }
  } else if(spinner_state == 2){
  //   roller->speed(roller->MAX);
  //   if(((PositionSysCamera*)ps)->isInTheVicinityOf(16, -4)) spinnerStep();
  //   else ((PositionSysCamera*)ps)->setMoveSetpoints(16, -4);
  // }else if(spinner_state == 3){
  //   drive->prepareDrive(0,0,0);
  //   if(millis() - spinner_timer > 750) spinnerStep();
  // }else if(spinner_state == 4){
    // drive->prepareDrive(45, 50, 0);
    drive->prepareDrive(70, 40, 0);
    if( ((LineSysCameraRR*)ls)->tookLine ) {
      spinner_state = 5;
      spinner_timer  = millis();
    }
  }else if(spinner_state == 5){
    roller->speed(roller->MIN);
    if(millis()-spinner_timer > 1500) spinnerStep();
  }else if(spinner_state == 6){
    drive->prepareDrive(180, 30, 0);
    if(millis() - spinner_timer > 650) spinnerStep();
  }else if(spinner_state == 7){
    roller->speed(roller->MIN);
    drive->prepareDrive(0, 0, 55);
    if(millis() - spinner_timer > 1000) spinnerStep();
  }else if(spinner_state == 8){
    drive->prepareDrive(drive->directionAccountingForTilt(0, 90), 100, 90);
    if(millis() - spinner_timer > 400) spinnerStep();
  }else if(spinner_state == 9){
    drive->prepareDrive(drive->directionAccountingForTilt(180, 90), 50, 90);
    if(millis() - spinner_timer > 750) spinnerStep();
  }else if(spinner_state == 10){
    if(flip==0){
    if(((PositionSysCamera*)ps)->isInRoughVicinityOf(0, -4)) spinnerStep();
    else ((PositionSysCamera*)ps)->setMoveSetpoints(0, -4);
    }else{
    if(((PositionSysCamera*)ps)->isInRoughVicinityOf(0, -13)) spinnerStep();
    else ((PositionSysCamera*)ps)->setMoveSetpoints(0, -13);
    }
  }else ball_catch_state++;
}

/*
Ball catch state machine
0: go towards the ball, until it's been in robot's mouth for 250ms
1: slowly return facing to north (slowly otherwise we might lose the ball)
2: reach the spot
*/

void RoundRobin::catchBall(){

  // if(!ball->isInFront() && ball_catch_state != 3){
  //   ball_catch_state = 0;
  //   ball_catch_flag = false;
  //   ball_catch_tilt = 0;
  // }

  if(ball_catch_state == 0){
    ((LineSysCameraRR*)ls)->flag = true;

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

    ((LineSysCameraRR*)ls)->flag = false;
  }else if(ball_catch_state == 3){
    // this->spinner(25);
    this->push();
  }else if(ball_catch_state == 4){
    drive->prepareDrive(270, 50, 0);
    if(((LineSysCameraRR*)ls)->tookLine && CURRENT_DATA_READ.posx <= -10) ball_catch_state = 5;
  }else if(ball_catch_state == 5){
    if( ((LineSysCameraRR*)ls)->linetriggerI[1] || ((LineSysCameraRR*)ls)->linetriggerO[1] > 0) drive->prepareDrive(90, 50, 0); //with 2 and 4 you go right or left accordingly
    else if( ((LineSysCameraRR*)ls)->linetriggerI[3] || ((LineSysCameraRR*)ls)->linetriggerO[3] > 0 ) drive->prepareDrive(270, 50, 0);
    else drive->prepareDrive(0, 30, 0);
    if(CURRENT_DATA_READ.posy > 7) {
      ball_catch_state=0;
      
      flip = 1-flip;
      
      CURRENT_DATA_WRITE.IMUOffset = 180 * flip;
    }
  }else if(ball_catch_state==6) drive->prepareDrive(0,0,0);
}
