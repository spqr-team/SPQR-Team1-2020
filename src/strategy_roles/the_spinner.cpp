#include "strategy_roles/the_spinner.h"
#include "systems/position/positionsys_camera.h"
#include "vars.h"
#include "math.h"

Spinner::Spinner() : Game() {}
Spinner::Spinner(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_) {}

void Spinner::init() {}
void Spinner::realPlay() {
  if(current_spot_i >= spots.size()) return;

  current_spot = spots[current_spot_i];

  if(doingCircle){
    circle();
    return;
  }

  if (((PositionSysCamera*)ps)->isInTheVicinityOf(current_spot.x, current_spot.y)) {
    if(current_spot.x == 0 && current_spot.y == 0) {
      current_spot_i++;
      return;
    }
    doingCircle = true;
    firstCircle = true;
    step = 0;
  }
  else (((PositionSysCamera*)ps)->setMoveSetpoints(current_spot.x, current_spot.y));
}

void Spinner::circle(){
  if(millis() - t < 1000){
    if(step == 0) drive->prepareDrive(45, 50, 0);
    else if(step == 1) drive->prepareDrive(315, 50, 0);
    else if(step == 2) drive->prepareDrive(225, 50, 0);
    else if(step == 3) {
      if(firstCircle){
      drive->prepareDrive(135, 80, 0);
      firstCircle = false;
      }else doingCircle = false;
    }
  }else {
    step++;
    t = millis();
  }
  
}