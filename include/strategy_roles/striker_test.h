#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define TARGET_MAX_DIST 100
#define TARGET_MIN_DIST 80
#define TARGET_DIST (TARGET_MAX_DIST - TARGET_MIN_DIST)/2
#define ANGLE_SHIFT_STEP 15
#define STRIKER_SPD 50

class StrikerTest : public Game{

    public:
        StrikerTest();
        StrikerTest(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;
        void striker();
        void ballBack(); 

        int angleShift, angleDiff, robotAngle, newAngle, 
            moveAngle, robotX, robotY, robotX_new, robotY_new;  
};
