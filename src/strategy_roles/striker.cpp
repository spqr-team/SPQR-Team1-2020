#include "behaviour_control/status_vector.h"
#include "systems/position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "strategy_roles/striker.h"
#include "vars.h"

#include "math.h"


Striker::Striker() : Game() {
  init();
}

Striker::Striker(LineSystem* ls_, PositionSystem* ps_) : Game(ls_, ps_) {
  init();
}

void Striker::init(){
    atk_speed = 0;
    atk_direction = 0;
    cstorc = 0;
}

void Striker::realPlay(){
  if(CURRENT_DATA_READ.ballSeen) this->striker();
  else ((PositionSysCamera*)ps)->goCenter();
}

void Striker::striker() {
  if(CURRENT_DATA_READ.ballAngle>= 350 || CURRENT_DATA_READ.ballAngle<= 20)  {
    if(CURRENT_DATA_READ.ballDistance > 190) atk_direction = 0;
    else atk_direction = CURRENT_DATA_READ.ballAngle;
    atk_speed = GOALIE_ATKSPD_FRT;
  }

  if(CURRENT_DATA_READ.ballAngle>= 90 && CURRENT_DATA_READ.ballAngle<= 270) {
    ballBack();
    atk_speed = GOALIE_ATKSPD_BAK;                   
  }

    if(CURRENT_DATA_READ.ballAngle> 10   && CURRENT_DATA_READ.ballAngle<  30)   {
      atk_direction = CURRENT_DATA_READ.ballAngle+ GOALIE_ATKDIR_PLUSANG1;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(CURRENT_DATA_READ.ballAngle>= 30 && CURRENT_DATA_READ.ballAngle<  45)    {
      atk_direction = CURRENT_DATA_READ.ballAngle+ GOALIE_ATKDIR_PLUSANG2;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(CURRENT_DATA_READ.ballAngle>= 45 && CURRENT_DATA_READ.ballAngle<  90)    {
      atk_direction = CURRENT_DATA_READ.ballAngle+ GOALIE_ATKDIR_PLUSANG3;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(CURRENT_DATA_READ.ballAngle> 270 && CURRENT_DATA_READ.ballAngle<= 315)   {
      atk_direction = CURRENT_DATA_READ.ballAngle- GOALIE_ATKDIR_PLUSANG3_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(CURRENT_DATA_READ.ballAngle> 315 && CURRENT_DATA_READ.ballAngle<= 330)   {
      atk_direction = CURRENT_DATA_READ.ballAngle- GOALIE_ATKDIR_PLUSANG2_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }
    if(CURRENT_DATA_READ.ballAngle> 330 && CURRENT_DATA_READ.ballAngle<  350)   {
      atk_direction = CURRENT_DATA_READ.ballAngle- GOALIE_ATKDIR_PLUSANG1_COR;
      atk_speed = GOALIE_ATKSPD_LAT;
    }

  // if((CURRENT_DATA_READ.ballAngle>= 330 || CURRENT_DATA_READ.ballAngle<= 30) && CURRENT_DATA_READ.ballDistance > 190) {      //storcimento
  //   atk_speed = GOALIE_ATKSPD_STRK;                                          //dove i gigahertz hanno fallito
  //   drive->prepareDrive(atk_direction, atk_speed, cstorc);
  // }
  // else  
  drive->prepareDrive(atk_direction, atk_speed);
}



void Striker::ballBack() {
  int ball_degrees2;
  int dir;

  int plusang;
  if(CURRENT_DATA_READ.ballDistance > 130) plusang = GOALIE_ATKDIR_PLUSANGBAK;
  else plusang = 0;
  
  if(CURRENT_DATA_READ.ballAngle> 180) ball_degrees2 = CURRENT_DATA_READ.ballAngle- 360;
  else ball_degrees2 = CURRENT_DATA_READ.ballAngle;
  if(ball_degrees2 > 0) dir = CURRENT_DATA_READ.ballAngle+ plusang;              //45 con 8 ruote
  else dir = CURRENT_DATA_READ.ballAngle- plusang;                                 //45 con 8 ruote
  if(dir < 0) dir = dir + 360;
  else dir = dir;
  atk_direction = dir;
}


void Striker::storcimentoPorta() {
  if (CURRENT_DATA_READ.angleAtkFix >= 5 && CURRENT_DATA_READ.angleAtkFix <= 60) cstorc+=9;
  else if (CURRENT_DATA_READ.angleAtkFix  <= 355 && CURRENT_DATA_READ.angleAtkFix >= 210) cstorc-=9;
  else cstorc *= 0.9;
  cstorc = constrain(cstorc, -45, 45);
}