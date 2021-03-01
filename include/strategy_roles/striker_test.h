#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define TARGET_DIST 120
#define ATTACK_DIST 150
#define ANGLE_SHIFT_STEP 5
#define STRIKER_SPD 80

class StrikerTest : public Game{

    public:
        StrikerTest();
        StrikerTest(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;
        void striker();
        void ballBack(); 

        int atk_speed, atk_direction;
    
};
