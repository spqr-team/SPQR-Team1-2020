#include <Arduino.h>

#include "behaviour_control/status_vector.h"
#include "sensors/sensors.h"
#include "strategy_roles/keeper.h"
#include "strategy_roles/games.h"
#include "systems/position/positionsys_camera.h"
#include <Arduino.h>

int currentPosition = 0;

Keeper::Keeper() : Game()
{
    init();
}

Keeper::Keeper(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_)
{
    init();
}

void Keeper::init()
{
    shouldStrike = false;
}

void Keeper::realPlay()
{
    if (ball->ballSeen)
        keeper();
    else
        ps->centerGoal();
}

void Keeper::keeper()
{
    shouldStrike = false;

    if(CURRENT_DATA_READ.ballDistance < KEEPER_ATTACK_DISTANCE || (CURRENT_DATA_READ.ballAngle >= 90 && CURRENT_DATA_READ.ballAngle <= 270)){
        shouldStrike = true;
        return;
    }
    
    if(CURRENT_DATA_READ.ballAngle >= 340 || CURRENT_DATA_READ.ballAngle <= 20) currentPosition = currentPosition; //Unneeded, just here for clarity
    else if(CURRENT_DATA_READ.ballAngle > 20 && CURRENT_DATA_READ.ballAngle < 90) currentPosition ++;
    else if(CURRENT_DATA_READ.ballAngle > 270 && CURRENT_DATA_READ.ballAngle < 340) currentPosition --;
    else{
        shouldStrike = true;
    }

    currentPosition = constrain(currentPosition, KEEPER_POINT_LEFT, KEEPER_POINT_RIGHT);

    if(currentPosition == KEEPER_POINT_LEFT) ((PositionSysCamera*)ps)->setMoveSetpoints(KEEPER_POINT_LEFT_C, CAMERA_GOAL_Y);
    else if(currentPosition == KEEPER_POINT_CENTER) ((PositionSysCamera*)ps)->setMoveSetpoints(KEEPER_POINT_CENTER_C, CAMERA_GOAL_Y);
    else if(currentPosition == KEEPER_POINT_RIGHT) ((PositionSysCamera*)ps)->setMoveSetpoints(KEEPER_POINT_RIGHT_C, CAMERA_GOAL_Y);
}
