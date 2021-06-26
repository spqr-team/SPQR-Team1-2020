#include "strategy_roles/corner_kick_1.h"
#include <Bounce2.h>

CornerKick::CornerKick() : Game(){
    init();
}

CornerKick::CornerKick(LineSystem *ls_, PositionSystem *ps_) : Game(ls_,ps_){
  init();
} 

Bounce b = Bounce(); // Instantiate a Bounce object

void CornerKick::init(){
  b.attach(37, INPUT);
  b.interval(25);
}

void CornerKick::realPlay(){
  b.update();
    if(CURRENT_DATA_READ.ballSeen){
      if(b.fell()) kick_state = 0;
      this->kick();
    }
    else drive->prepareDrive(0,0,0);
}

void CornerKick::kick(){
    //DEBUG.println(kick_state);
  if(kick_state == 0){
    kicktimer = millis();
    kick_state++;
    kick_flag = false;
  } else if(kick_state == 1){
    drive->prepareDrive(0, 0, CURRENT_DATA_READ.ballAngleFix);
    if((CURRENT_DATA_READ.ballAngle >= 350 || CURRENT_DATA_READ.ballAngle <= 10) && millis() - kicktimer > 250) kick_state ++;
  } else if(kick_state==2){
    drive->prepareDrive(0, 60, CURRENT_DATA_READ.ballAngleFix);
    if(ball->isInMouth()){
      kick_state++;
      if(!kick_flag) {
        kick_flag = true;
        kicktimer = millis();
      }else{
        if(kick_flag && millis() - kicktimer > 700){
          kick_flag = false;
          kick_state++;
          kicktimer = millis();
        }
      }
    }
  } else if(kick_state==3){
    drive->prepareDrive(0, 150, CURRENT_DATA_READ.ballAngleFix);
    if(millis()-kicktimer > 400){
        kick_state++;
    }
  } else if(kick_state==4){
    if(((PositionSysCamera*)ps)->isAtDistanceFrom(0, -28, 5)) {
      kick_state++;
      kicktimer = millis();
    }else (((PositionSysCamera*)ps)->setMoveSetpoints(0, -28));
  } else if(kick_state == 5){
    drive->prepareDrive(0,0,0);
    bt->can_send = true;
    bt->tosend = 'C';
    if(millis() - kicktimer > 500){
      kick_state++;
      tone(BUZZER, 220, 250);
      kicktimer = millis();
    }
  } else if(kick_state == 6){
    bt->can_send = true;
    bt->tosend = 'B';
    if(millis() - kicktimer > 750){
      kick_state++;
      kicktimer = millis();
      bt->can_send = false;
  }
  }else if (kick_state == 7) {
    bt->can_send = false;
    drive->prepareDrive(0,0,0);
  }
}