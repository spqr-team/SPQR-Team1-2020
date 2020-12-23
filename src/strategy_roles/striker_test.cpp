#include "behaviour_control/status_vector.h"
#include "sensors/sensors.h"
#include "strategy_roles/striker_test.h"
#include "vars.h"

#include "math.h"

StrikerTest::StrikerTest() : Game() {
  init();
}

StrikerTest::StrikerTest(LineSystem* ls_, PositionSystem* ps_) : Game(ls_, ps_) {
  init();
}

void StrikerTest::init(){
    atk_speed = 0;
    atk_direction = 0;
}

void StrikerTest::realPlay(){
  if(CURRENT_DATA_READ.ballSeen) striker();
  else drive->prepareDrive(0,0,0);
}

void StrikerTest::striker() {
  if(CURRENT_DATA_READ.ballAngle>= 350 || CURRENT_DATA_READ.ballAngle<= 20)  {
    if(CURRENT_DATA_READ.ballDistance > 190) atk_direction = 0;
    else atk_direction = CURRENT_DATA_READ.ballAngle;
    atk_speed = GOALIE_ATKSPD_FRT;
  }

  if(CURRENT_DATA_READ.ballAngle>= 90 && CURRENT_DATA_READ.ballAngle<= 270) {
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

  drive->prepareDrive(atk_direction, atk_speed);
}



void StrikerTest::ballBack() {
}