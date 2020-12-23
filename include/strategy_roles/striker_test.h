#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define TILT_MULT 1.8
#define TILT_DIST 170
#define CATCH_DIST 150
#define GOALIE_ATKSPD_LAT  120 //255
#define GOALIE_ATKSPD_BAK  120
#define GOALIE_ATKSPD_FRT  120
#define GOALIE_ATKSPD_STRK 120
#define GOALIE_ATKDIR_PLUSANG1 20
#define GOALIE_ATKDIR_PLUSANG2 35
#define GOALIE_ATKDIR_PLUSANG3 40
#define GOALIE_ATKDIR_PLUSANGBAK 40
#define GOALIE_ATKDIR_PLUSANG1_COR 60
#define GOALIE_ATKDIR_PLUSANG2_COR 70
#define GOALIE_ATKDIR_PLUSANG3_COR 70

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
