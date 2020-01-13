#pragma once

#include "vars.h"
#include "sensors.h"
#include "systems.h"

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