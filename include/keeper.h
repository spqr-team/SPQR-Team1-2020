#pragma once

#include "game.h"

#define KEEPER_ATTACK_DISTANCE 190
#define KEEPER_ALONE_ATTACK_TIME 5000 //in millis
#define KEEPER_COMRADE_ATTACK_TIME 3000//in millis
#define KEEPER_BASE_VEL 320
#define KEEPER_VEL_MULT 1.4
#define KEEPER_BALL_BACK_ANGLE 30
#define KEEPER_ANGLE_SX 265
#define KEEPER_ANGLE_DX 85

//POSITION
#define CENTERGOALPOST_VEL1 220
#define CENTERGOALPOST_VEL2 220
#define CENTERGOALPOST_VEL3 220
#define CENTERGOALPOST_CAM_MIN -40
#define CENTERGOALPOST_CAM_MAX 40
#define CENTERGOALPOST_US_MAX 60
#define CENTERGOALPOST_US_CRITIC 25

class Keeper : public Game{

    public:
        Keeper();
        Keeper(LineSystem*, PositionSystem*);

    private:
        void realPlay() override;
        void init() override;
        void keeper();
        void centerGoalPostCamera(bool);

        int defSpeed, defDir;

        float angle, angleX, angleY;
        elapsedMillis t, toh, keeperAttackTimer;
        bool keeper_tookTimer, keeper_backToGoalPost;
};
