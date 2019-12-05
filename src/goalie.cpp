#include "goalie.h"

Goalie::Goalie(){ } 

void Goalie::goalie(){
    digitalWrite(LED_G, HIGH);
    if(ball->ballSeen){
        if(ball->angle >= 0 && ball->angle < 45) drive->prepareDrive(0, 75, 0);
        /* else if(ball->angle >= 45 && ball->angle <= 60) drive->drive(ball->angle, 75, 0);
        else if(ball->angle > 60 && ball->angle < 90) drive->drive(ball->angle, 75, 0);
        else if(ball->angle >= 90 && ball->angle < 135) drive->drive(ball->angle, 75, 0);  */
    } else {
        drive->prepareDrive(0, 0, 0);
        drive->drive(0, 0, 0);
    } 
}

void Goalie::ballBack(){
/* old    int ballangle2;
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
  atk_direction = dir; */
}