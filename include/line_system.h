#pragma once
#include "ds_ctrl_lines.h"
#include "games.h"
#include "game.h"

class LineSystem : public DSCtrlLines{
    public:
        LineSystem(DSCtrlLines* method, Game* strategy);
        virtual void update() = 0;
        virtual void test() = 0;
};