#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define STRIKER_ATTACK_DISTANCE 300
#define STRIKER_PLUSANG 55
#define STRIKER_PLUSANG_VISIONCONE 20

class Striker : public Game{

    public:
        Striker();
        Striker(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;
        void striker();
        void ballBack(); 
        void storcimentoPorta();

        int atk_speed, atk_direction;
        float cstorc;

    
};
