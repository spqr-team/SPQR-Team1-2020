#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define X_COORD 10
#define Y_COORD 15

class SpotFinder : public Game{

    public:
        SpotFinder();
        SpotFinder(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;

        unsigned long t = 0;
};
