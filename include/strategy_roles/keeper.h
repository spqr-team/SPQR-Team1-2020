#pragma once

#include "strategy_roles/game.h"
#include "systems/position/positionsys_camera.h"

#define KEEPER_3_POINTS
//#define KEEPER_5_POINTS
#ifdef KEEPER_3_POINTS
#define KEEPER_POINT_LEFT -1
#define KEEPER_POINT_CENTER 0
#define KEEPER_POINT_RIGHT 1
#define KEEPER_POINT_LEFT_C CAMERA_GOAL_MIN_X
#define KEEPER_POINT_CENTER_C CAMERA_GOAL_X
#define KEEPER_POINT_RIGHT_C CAMERA_GOAL_MAX_X
#endif
#define KEEPER_ATTACK_DISTANCE 100

class Keeper : public Game{

    public:
        Keeper();
        Keeper(LineSystem*, PositionSystem*);
        
    public:
        bool shouldStrike;

    private:
        void realPlay() override;
        void init() override;
        void keeper();

        int point_spacing, ball_x;
};
