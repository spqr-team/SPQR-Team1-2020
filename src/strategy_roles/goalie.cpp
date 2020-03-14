#include "behaviour_control/status_vector.h"
#include "position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "strategy_roles/goalie.h"
#include "vars.h"

#include "math.h"


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
  else ((PositionSysCamera*)ps)->goCenter();
}

int dir, degrees2;
void Goalie::goalie(int plusang) {
  if(ball->distance < CATCH_DIST) drive->prepareDrive(ball->angle, 350, 0);
  else{
/*     if(ball->angle > 345 || ball->angle < 15) plusang *= 0.15;
    FRONT */
    if (ball->angle > 345 && ball->angle < 15) plusang *= 0.15;
    if(ball->angle > 180) degrees2 = ball->angle - 360;
    else degrees2 = ball->angle;

    if(degrees2 > 0) dir = ball->angle + plusang;              //45 con 8 ruote
    else dir = ball->angle - plusang;                          //45 con 8 ruote

    if(dir < 0) dir = dir + 360;
    else dir = dir;

    storcimentoPorta();
    if(ball->distance > TILT_DIST && (ball->angle > 340 || ball->angle < 20)){
      plusang -= 20;
      drive->prepareDrive(dir, 350, cstorc);
    } else {
      drive->prepareDrive(dir, 350, 0);
      cstorc = 0;
    }
  }
}

void Goalie::storcimentoPorta() {
  if (CURRENT_DATA_READ.angleAtkFix >= 5 && CURRENT_DATA_READ.angleAtkFix <= 60) cstorc+=9;
  else if (CURRENT_DATA_READ.angleAtkFix  <= 355 && CURRENT_DATA_READ.angleAtkFix >= 210) cstorc-=9;
  else cstorc *= 0.9;
  cstorc = constrain(cstorc, -45, 45);
}