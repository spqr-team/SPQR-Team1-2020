#pragma once

#include "game.h"

//KEEPER
#define KEEPER_ATTACK_DISTANCE 200
#define KEEPER_ALONE_ATTACK_TIME 5000 //in millis
#define KEEPER_COMRADE_ATTACK_TIME 3000//in millis
#define KEEPER_BASE_VEL 320
#define KEEPER_VEL_MULT 1.4
#define KEEPER_BALL_BACK_ANGLE 30


class Keeper : public Game{

    public:
        Keeper();
    private:
        void realPlay() override;
        void keeper();

        int defSpeed, defDir;

        float angle, angleX, angleY;
        elapsedMillis t, toh, keeperAttackTimer;
        bool keeper_tookTimer, keeper_backToGoalPost;
};
