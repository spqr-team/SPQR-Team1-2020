#include <Arduino.h>

#include "behaviour_control/status_vector.h"
#include "sensors/sensors.h"
#include "strategy_roles/keeper.h"
#include "strategy_roles/games.h"
#include "systems/position/positionsys_camera.h"
#include <Arduino.h>

Keeper::Keeper() : Game()
{
    init();
}

Keeper::Keeper(LineSystem *ls_, PositionSystem *ps_) : Game(ls_, ps_)
{
}

void Keeper::init()
{
    point_spacing = (abs(CAMERA_GOAL_MIN_X) + abs(CAMERA_GOAL_MAX_X)) / KEEPER_N_POINTS;
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
    //Convert Ball position into a coordinate in the Camera Position Sys plane
    float ball_x = cos((-90 + CURRENT_DATA_READ.ballAngle) * 3.14 / 180);
    // Remap between GOAL positions
    ball_x = (int)map(ball_x, -1, 1, CAMERA_GOAL_MIN_X, CAMERA_GOAL_MAX_X);

    // for (int i = CAMERA_GOAL_MIN_X; i <= CAMERA_GOAL_MAX_X; i += point_spacing)
    //     if (ball_x < i)
    //     {
            ((PositionSysCamera *)ps)->setMoveSetpoints(ball_x, CAMERA_GOAL_Y);
        //     break;
        // }
}
