#pragma once

#include "systems/position/positionsys_camera.h"
#include "systems/lines/linesys_camera.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"
#include "strategy_roles/games.h"
#include "behaviour_control/status_vector.h"
#include "sensors/data_source_ball.h"
#include "strategy_roles/striker.h"
#include "sensors/data_source_ball_presence.h"
#include "sensors/data_source_bt.h"
#include "vars.h"

class CornerKick : public Game{
    public:
        CornerKick();
        CornerKick(LineSystem* ls, PositionSystem* ps);

        void init() override;
        void realPlay() override;
        void kick();
        unsigned long kicktimer = 0, debounce_timer = 0;
        int kick_state = 99;
        bool kick_flag = false;

        int old_btn = 0, new_val = 0;
        ComplementaryFilter* ballAngleFilter = new ComplementaryFilter(0.85);
};