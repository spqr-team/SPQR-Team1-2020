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

    storcimentoPorta();
    if(ball->distance > 200 && (ball->angle > 340 || ball->angle < 20)) drive->prepareDrive(ball->dir, 150, cstorc);
    else {
      drive->prepareDrive(ball->dir, 150, 0);
      cstorc = 0;
    }
  }
}

void Goalie::storcimentoPorta() {
  if (camera->getValueAtk(false) >= 10 && camera->getValueAtk(false) <= 90) cstorc+=9;
  else if (camera->getValueAtk(false)  <= 350 && camera->getValueAtk(false) >= 270) cstorc-=9;
  // else cstorc *= 0.7;
  cstorc = constrain(cstorc, -45, 45);
}