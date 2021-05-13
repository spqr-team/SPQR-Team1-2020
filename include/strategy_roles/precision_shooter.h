#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define PS_ATTACK_DISTANCE 110
#define PS_TILT_STOP_DISTANCE 140
#define PS_PLUSANG 55
#define PS_PLUSANG_VISIONCONE 7

class PrecisionShooter : public Game{

    public:
        PrecisionShooter();
        PrecisionShooter(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;
        void striker();
        int tilt();

        int atk_speed, atk_direction, atk_tilt;
        float cstorc;

        bool gotta_tilt;
};
