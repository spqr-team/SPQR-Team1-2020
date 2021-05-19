#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define PAS_ATTACK_DISTANCE 110
#define PAS_TILT_STOP_DISTANCE 140
#define PAS_PLUSANG 55
#define PAS_PLUSANG_VISIONCONE 10

class PassAndShoot : public Game{

    public:
        PassAndShoot();
        PassAndShoot(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;
        void striker();
        int tilt();

        int atk_speed, atk_direction, atk_tilt;
        float cstorc;
        unsigned long pass_counter;
        bool gotta_tilt;
};
