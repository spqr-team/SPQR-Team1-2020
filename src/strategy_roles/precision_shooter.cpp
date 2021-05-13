#include "behaviour_control/status_vector.h"
#include "systems/position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "sensors/data_source_ball.h"
#include "strategy_roles/precision_shooter.h"
#include "vars.h"
#include "math.h"


PrecisionShooter::PrecisionShooter() : Game()
{
  init();
}

PrecisionShooter::PrecisionShooter(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_)
{
  init();
}

void PrecisionShooter::init()
{
  atk_speed = 0;
  atk_direction = 0;
  atk_tilt = 0;
  cstorc = 0;

  gotta_tilt = false;
}

void PrecisionShooter::realPlay()
{
  if (CURRENT_DATA_READ.ballSeen)
    this->striker();
  else
    ps->goCenter();
}

unsigned long t3 = 0;
unsigned long t4 = 0;
boolean ignited = false;

void PrecisionShooter::striker(){

  #ifdef MAX_VEL
  #undef MAX_VEL
  #define MAX_VEL 100
  #endif

  //seguo palla
  int ball_degrees2, dir, ball_deg = CURRENT_DATA_READ.ballAngle, plusang =  PS_PLUSANG;
  
  if(ball_deg >= 346 || ball_deg <= 16) plusang = PS_PLUSANG_VISIONCONE;            //se ho la palla in un range di +-20 davanti, diminuisco di 20 il plus
  if(ball_deg > 180) ball_degrees2 = ball_deg - 360;            //ragiono in +180 -180  
  else ball_degrees2 = ball_deg;

  if(ball_degrees2 > 0) dir = ball_deg + plusang;               //se sto nel quadrante positivo aggiungo
  else dir = ball_deg - plusang;                                //se sto nel negativo sottraggo

  dir = (dir + 360) % 360;
  drive->prepareDrive(dir, MAX_VEL_HALF, tilt());

  if(ball->isInFront()) roller->speed(ROLLER_DEFAULT_SPEED);
  else roller->speed(roller->MIN);

  if(ball->isInFront() && CURRENT_DATA_READ.ballDistance <= 78 && ( (CURRENT_DATA_READ.posy >= 32 &&  (CURRENT_DATA_READ.posx >= 15  || CURRENT_DATA_READ.posx <= -15)) ||  abs(tilt()) > 65 ) ) {
    // Just let the robot slowly approach the ball
    if(!ignited){
      ignited = true;
      t4 = millis();
    }
    if(millis() - t4 > 250  && ignited){
      t3 = millis();
    }
  }

  if(millis() - t3 < 800){
    roller->speed(roller->MAX);
    drive->prepareDrive(180, MAX_VEL_3QUARTERS, 0);
    ignited = false;
  }


  
}

int PrecisionShooter::tilt() {
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