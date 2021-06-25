#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "behaviour_control/complementary_filter.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define RR_ATTACK_DISTANCE 110
#define RR_TILT_STOP_DISTANCE 140
#define RR_PLUSANG 55
#define RR_PLUSANG_VISIONCONE 10

// There needs to be a little bit of space between the target point and the spot to be in
#define RR_SPINNER_OVERHEAD 7

#define RR_KICK_LIMIT_TILT1 200
#define RR_KICK_LIMIT_MAX 315
#define RR_KICK_LIMIT_MIN 45

#define ROUND_ROBIN_VEL 30
#define RR_YCOORD -5
#define RR_ROLLER_SPD 1500

class RoundRobin : public Game{

    public:
        RoundRobin();
        RoundRobin(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;
        void catchBall();
        void spinner(int);
        void push();
        void spinnerStep();
        
    private:
        int atk_speed, atk_direction, atk_tilt;
        float cstorc;
        bool gotta_tilt;
        ComplementaryFilter* ballAngleFilter;

        int flip = 0;

        float tilt1 = 0;
        float tilt2 = 0;
        int spinner_state = 0;
        bool spinner_flag = false;
        unsigned long spinner_timer = 0;
        float spinner_tilt = 0;
        int ball_catch_state = 0;
        bool ball_catch_flag = false;
        unsigned long ball_catch_timer = 0;
        float ball_catch_tilt = 0;
        int limitx = 0;
};
