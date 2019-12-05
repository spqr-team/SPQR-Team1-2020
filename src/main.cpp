#include <Arduino.h>

#include "game.h"
#include "goalie.h"

class Trial{
  public:
  void trial(){
    digitalWrite(LED_Y, LOW);
  if(ball->angle >= 350 || ball->angle <= 10)  {
    if(ball->distance > 190) goalie->atk_direction = 0;
    else goalie->atk_direction = ball->angle;
    goalie->atk_speed = GOALIE_ATKSPD_FRT;
  }

  if(ball->angle >= 90 && ball->angle <= 270) {
    goalie->ballBack();
    goalie->atk_speed = GOALIE_ATKSPD_BAK;                   
  }
  if(digitalRead(SWITCH_DX) == 1) {
    if(ball->angle > 10   && ball->angle <  30)   {
      goalie->atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG1;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle >= 30 && ball->angle <  45)    {
      goalie->atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG2;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle >= 45 && ball->angle <  90)    {
      goalie->atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG3;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 270 && ball->angle <= 315)   {
      goalie->atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG3_COR;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 315 && ball->angle <= 330)   {
      goalie->atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG2_COR;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 330 && ball->angle <  350)   {
      goalie->atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG1_COR;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
  } else {
    if(ball->angle > 10   && ball->angle <  30)   {
      goalie->atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG1_COR;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle >= 30 && ball->angle <  45)    {
      goalie->atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG2_COR;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle >= 45 && ball->angle <  90)    {
      goalie->atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG3_COR;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 270 && ball->angle <= 315)   {
      goalie->atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG3;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 315 && ball->angle <= 330)   {
      goalie->atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG2;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 330 && ball->angle <  350)   {
      goalie->atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG1;
      goalie->atk_speed = GOALIE_ATKSPD_LAT;
    }
  }

  if((ball->angle >= 330 || ball->angle <= 30) && ball->distance > 190) {      //storcimento
    goalie->atk_speed = GOALIE_ATKSPD_STRK;                                             //dove i gigahertz hanno fallito
    drive->prepareDrive(goalie->atk_direction, goalie->atk_speed, 0);
  }
  else drive->prepareDrive(goalie->atk_direction, goalie->atk_speed, 0);
}

};


void setup() {
  delay(500);

  DEBUG.begin(9600);
  initSensors();
  delay(2000);
}

void loop() {
  updateSensors();
  Trial trial;
  trial.trial();
  //drive->prepareDrive(0,0,0);
  //linesCtrl->update();
 
  drive->drivePrepared();

} 
