#pragma once

#include "vars.h"
#include "sensors.h"

class Game {
    public:
        Game();
        void play(bool condition=true);
    private:
        virtual void realPlay() = 0;
};