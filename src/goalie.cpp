#include "goalie.h"
#include "sensors.h"
#include "vars.h"
#include "positionsys_zone.h"

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
  if(ball->ballSeen) this->goalie(45);
  else ((PositionSysZone*)ps)->goCenter();
}

int dir, degrees2;
void Goalie::goalie(int plusang) {
  if(ball->distance < 185) drive->prepareDrive(ball->angle, 350, 0);
  else{
    if(ball->angle > 340 || ball->angle < 20) plusang -= 20;
    if(ball->angle > 180) degrees2 = ball->angle - 360;
    else degrees2 = ball->angle;

    if(degrees2 > 0) dir = ball->angle + plusang;              //45 con 8 ruote
    else dir = ball->angle - plusang;                                 //45 con 8 ruote

    if(dir < 0) dir = dir + 360;
    else dir = dir;

    storcimentoPorta();
    if(ball->distance > 200 && (ball->angle > 340 || ball->angle < 20)) drive->prepareDrive(dir, 350, cstorc);
    else {
      drive->prepareDrive(dir, 350, 0);
      cstorc = 0;
    }
  }
}

void Goalie::storcimentoPorta() {
  if (camera->getValueAtk(true ) >= 10 && camera->getValueAtk(true) <= 90) cstorc+=9;
  else if (camera->getValueAtk(true)  <= 350 && camera->getValueAtk(true) >= 270) cstorc-=9;
  // else cstorc *= 0.7;
  cstorc = constrain(cstorc, -45, 45);
}