#include "goalie.h"
#include "sensors.h"
#include "vars.h"

Goalie::Goalie() : Game() {
  init();
}

Goalie::Goalie(LineSystem* ls_, PositionSystem* ps_) : Game(ls_, ps_) {
  init();
}

void Goalie::init(){
    atk_speed = 0;
    atk_direction = 0;
    cstorc = 0;
}

void Goalie::realPlay(){
  if(ball->ballSeen) this->goalie(50);
  else drive->prepareDrive(0,0,0);
}

void Goalie::goalie(int plusang) {
  if(ball->distance < 185) drive->prepareDrive(ball->angle, 350, 0);
  else{
    if(ball->angle > 340 || ball->angle < 20) plusang -= 20;
    if(ball->angle > 180) ball->degrees2 = ball->angle - 360;
    else ball->degrees2 = ball->angle;

    if(ball->degrees2 > 0) ball->dir = ball->angle + plusang;              //45 con 8 ruote
    else ball->dir = ball->angle - plusang;                                 //45 con 8 ruote

    if(ball->dir < 0) ball->dir = ball->dir + 360;
    else ball->dir = ball->dir;
    ball->b = ball->dir;
    drive->prepareDrive(ball->dir, 300, 0);
  }
 /*  drive->speed = 300;
  drive->dir = drive->dir; */
  /* if(ball->angle >= 350 || ball->angle <= 10)  {
    if(ball->distance > 190) atk_direction = 0;
    else atk_direction = ball->angle;
    atk_speed = GOALIE_ATKSPD_FRT;
  }

  if(ball->angle >= 90 && ball->angle <= 270) {
    this->ballBack();
    atk_speed = GOALIE_ATKSPD_BAK;                   
  }
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

  this->storcimentoPorta();
  if((ball->angle >= 330 || ball->angle <= 30) && ball->distance > 190) {      //storcimento
    atk_speed = GOALIE_ATKSPD_STRK;                                             //dove i gigahertz hanno fallito
    drive->prepareDrive(atk_direction, atk_speed, cstorc);
  }
  else  drive->prepareDrive(atk_direction, atk_speed); */
}

void Goalie::storcimentoPorta() {
  if (camera->getValueAtk(true) >= 3) cstorc+=9;
  else if (camera->getValueAtk(true)  < -3) cstorc-=9;
  else cstorc *= 0.7;
  cstorc = constrain(cstorc, -45, 45);
}

void Goalie::ballBack() {

/*   if(ball->distance > 130) ball->plusang = GOALIE_ATKDIR_PLUSANGBAK;
  else ball->plusang = 0;
  
  if(ball->angle > 180) ball->degrees2 = ball->angle - 360;
  else ball->degrees2 = ball->angle;
  if(ball->degrees2 > 0) ball->dir = ball->angle + ball->plusang;              //45 con 8 ruote
  else ball->dir = ball->angle - ball->plusang;                                 //45 con 8 ruote
  if(ball->dir < 0) ball->dir = ball->dir + 360;
  else ball->dir = ball->dir;
  atk_direction = ball->dir; */
}