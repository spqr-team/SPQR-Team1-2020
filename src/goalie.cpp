#include "goalie.h"

/* Goalie::Goalie(){
    digitalWrite(LED_Y, LOW);
} */

/* void Goalie::goalie(){
    digitalWrite(LED_Y, LOW);
  if(ball->angle >= 350 || ball->angle <= 10)  {
    if(ball->distance > 190) atk_direction = 0;
    else atk_direction = ball->angle;
    atk_speed = GOALIE_ATKSPD_FRT;
  }

  if(ball->angle >= 90 && ball->angle <= 270) {
    ballBack();
    atk_speed = GOALIE_ATKSPD_BAK;                   
  }
  if(digitalRead(SWITCH_DX) == 1) {
    if(ball->angle > 10   && ball->angle <  30)   {
      atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG1;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle >= 30 && ball->angle <  45)    {
      atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG2;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle >= 45 && ball->angle <  90)    {
      atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG3;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 270 && ball->angle <= 315)   {
      atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG3_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 315 && ball->angle <= 330)   {
      atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG2_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 330 && ball->angle <  350)   {
      atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG1_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
  } else {
    if(ball->angle > 10   && ball->angle <  30)   {
      atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG1_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle >= 30 && ball->angle <  45)    {
      atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG2_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle >= 45 && ball->angle <  90)    {
      atk_direction = ball->angle + GOALIE_ATKDIR_PLUSANG3_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 270 && ball->angle <= 315)   {
      atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG3;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 315 && ball->angle <= 330)   {
      atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG2;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(ball->angle > 330 && ball->angle <  350)   {
      atk_direction = ball->angle - GOALIE_ATKDIR_PLUSANG1;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
  }

  if((ball->angle >= 330 || ball->angle <= 30) && ball->distance > 190) {      //storcimento
    atk_speed = GOALIE_ATKSPD_STRK;                                             //dove i gigahertz hanno fallito
    drive->prepareDrive(atk_direction, atk_speed, 0);
  }
  else drive->prepareDrive(atk_direction, atk_speed, 0);
   /*  digitalWrite(LED_G, HIGH);
    if(ball->ballSeen){
        if(ball->angle >= 0 && ball->angle < 45) drive->drive(ball->angle, 75, 0);
        else if(ball->angle >= 45 && ball->angle <= 60) drive->drive(ball->angle, 75, 0);
        else if(ball->angle > 60 && ball->angle < 90) drive->drive(ball->angle, 75, 0);
        else if(ball->angle >= 90 && ball->angle < 135) drive->drive(ball->angle, 75, 0); 
    } else {
        drive->prepareDrive(0, 0, 0);
        drive->drive(0, 0, 0);
    } */

void Goalie::ballBack(){
    int ballangle2;
    int dir;
    int plusang;
    
  if(ball->distance > 130) plusang = GOALIE_ATKDIR_PLUSANGBAK;
  else plusang = 0;
  
  if(ball->angle > 180) ballangle2 = ball->angle - 360;
  else ballangle2 = ball->angle;
  if(ballangle2 > 0) dir = ball->angle + plusang;              //45 con 8 ruote
  else dir = ball->angle - plusang;                                 //45 con 8 ruote
  if(dir < 0) dir = dir + 360;
  else dir = dir;
  atk_direction = dir;
}