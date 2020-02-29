#pragma once

#include "vars.h"
#include "position/systems.h"
#include "sensors/sensors.h"

class Game {
    public:
        Game();
        Game(LineSystem* ls, PositionSystem* ps);
        void play(bool condition=true);
        LineSystem* ls;
        PositionSystem* ps;
    private:
        virtual void realPlay() = 0;
        virtual void init() = 0;
};