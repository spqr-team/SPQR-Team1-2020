#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"


#define CK2_SPINNER_OVERHEAD 10

#define CK2_KICK_LIMIT_TILT1 200
#define CK2_KICK_LIMIT_MAX 315
#define CK2_KICK_LIMIT_MIN 45

class CornerKick2 : public Game{

    public:
        CornerKick2();
        CornerKick2(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;

        void catchBall();
        void spinner(int);

        unsigned long timer = 0;
        int state = 0;

        int ball_catch_state = 0;
        int ball_catch_timer = 0;
        bool ball_catch_flag = false;
        float ball_catch_tilt = 0;

        int goal_coords = 0;

        ComplementaryFilter* ballAngleFilter = new ComplementaryFilter(0.85);

        int limitx = 0, spinner_state = 0;
        bool spinner_flag = false;
        float tilt1 = 0, tilt2 = 0, spinner_tilt = 0;
        unsigned long spinner_timer = 0;
};
