#include "strategy_roles/spot_finder.h"
#include "systems/position/positionsys_camera.h"
#include "vars.h"
#include "math.h"

SpotFinder::SpotFinder() : Game() {}
SpotFinder::SpotFinder(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_) {}

void SpotFinder::init() {}
void SpotFinder::realPlay() {
  if(millis() - t > 150){

    int zone = 6;

    if(CURRENT_DATA_READ.posx >= -X_COORD && CURRENT_DATA_READ.posx <= X_COORD  && CURRENT_DATA_READ.posy >= -Y_COORD && CURRENT_DATA_READ.posy <= Y_COORD)  BALL_32U4.write(0b000000110); //center
    else if(CURRENT_DATA_READ.posx <= -X_COORD && CURRENT_DATA_READ.posy <= -Y_COORD) BALL_32U4.write(0b00000100); //bottom left
    else if(CURRENT_DATA_READ.posx <= -X_COORD && CURRENT_DATA_READ.posy >= Y_COORD) BALL_32U4.write(2); //top left
    else if(CURRENT_DATA_READ.posx >= X_COORD && CURRENT_DATA_READ.posy <= -Y_COORD) BALL_32U4.write(0b00000001); //bottom right
    else if(CURRENT_DATA_READ.posx >= X_COORD && CURRENT_DATA_READ.posy >= Y_COORD) BALL_32U4.write(5); //top right
    else BALL_32U4.write(0);

    // if( ((PositionSysCamera*)ps)->isInRoughVicinityOf(-X_COORD,-Y_COORD) ) BALL_32U4.write(1); //bottom left
    // else if( ((PositionSysCamera*)ps)->isInRoughVicinityOf(-X_COORD,Y_COORD) ) BALL_32U4.write(2); //top left
    // else if( ((PositionSysCamera*)ps)->isInRoughVicinityOf(0,0) ) BALL_32U4.write(3); //center
    // else if( ((PositionSysCamera*)ps)->isInRoughVicinityOf(X_COORD,-Y_COORD) ) BALL_32U4.write(4); //bottom right
    // else if( ((PositionSysCamera*)ps)->isInRoughVicinityOf(X_COORD,Y_COORD) ) BALL_32U4.write(5); //top right

    t = millis();


  }
  drive->stopAll();
}