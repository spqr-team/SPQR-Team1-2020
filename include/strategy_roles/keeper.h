#pragma once

#include "strategy_roles/game.h"

#define KEEPER_N_POINTS 3

class Keeper : public Game{

    public:
        Keeper();
        Keeper(LineSystem*, PositionSystem*);

    private:
        void realPlay() override;
        void init() override;
        void keeper();

        int point_spacing, ball_x;
};
