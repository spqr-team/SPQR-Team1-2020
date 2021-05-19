#include "behaviour_control/status_vector.h"
#include "systems/position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "sensors/data_source_ball.h"
#include "strategy_roles/pass_and_shoot.h"
#include "vars.h"
#include "math.h"


PassAndShoot::PassAndShoot() : Game()
{
  init();
}

PassAndShoot::PassAndShoot(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_)
{
  init();
}

void PassAndShoot::init()
{
  atk_speed = 0;
  atk_direction = 0;
  atk_tilt = 0;
  cstorc = 0;

  gotta_tilt = false;

  pass_counter = millis();
}

unsigned long pass_timer = 0;
boolean flag = false;

void PassAndShoot::realPlay()
{
  if (CURRENT_DATA_READ.ballSeen){
    if(robot_indentifier == HIGH){
        if(ball->isInFront() && CURRENT_DATA_READ.ballDistance <= 90){
          if(!flag){
            pass_timer = millis();
            flag = true;

            //Show on 32u4
            Serial2.write(0b00000100);
          }
        }
        if(!flag || (millis() - pass_timer <= 650)){
          striker();
        }else{
        ((PositionSysCamera*)ps)->setMoveSetpoints(CAMERA_GOAL_MIN_X, CAMERA_GOAL_Y);
        bt->tosend = 'C';
        roller->speed(0);
        }
    }else{
      if(bt->received == 'C'){
        striker();
      }else drive->prepareDrive(0,0,0);
    }
  }else drive->prepareDrive(0,0,0);


    
}

void PassAndShoot::striker(){

  #ifdef MAX_VEL
  #undef MAX_VEL
  #define MAX_VEL 100
  #endif

  //seguo palla
  int ball_degrees2, dir, ball_deg = CURRENT_DATA_READ.ballAngle, plusang =  PAS_PLUSANG;
  
  if(ball_deg >= 346 || ball_deg <= 16) plusang = PAS_PLUSANG_VISIONCONE;            //se ho la palla in un range di +-20 davanti, diminuisco di 20 il plus
  if(ball_deg > 180) ball_degrees2 = ball_deg - 360;            //ragiono in +180 -180  
  else ball_degrees2 = ball_deg;

  if(ball_degrees2 > 0) dir = ball_deg + plusang;               //se sto nel quadrante positivo aggiungo
  else dir = ball_deg - plusang;                                //se sto nel negativo sottraggo

  dir = (dir + 360) % 360;
  drive->prepareDrive(dir, MAX_VEL_HALF, tilt());

  if(ball->isInFront()) roller->speed(ROLLER_DEFAULT_SPEED);
  else roller->speed(roller->MIN);
  
}

int PassAndShoot::tilt() {
  if (ball->isInFront() && CURRENT_DATA_READ.ballDistance <= 90 /* || (ball->isInMouthMaxDistance() && gotta_tilt)*/ ) gotta_tilt = true;
  else gotta_tilt = false;

  if(!gotta_tilt || !CURRENT_DATA_READ.atkSeen) {
    atk_tilt *= 0.8;
    if(atk_tilt <= 10) atk_tilt = 0;
  }else{
    atk_tilt = roller->roller_armed ? CURRENT_DATA_READ.angleAtkFix : constrain(CURRENT_DATA_READ.angleAtkFix, -45, 45);
  }

  return atk_tilt;
}