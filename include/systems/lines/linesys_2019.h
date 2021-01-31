#pragma once

#include <Arduino.h>

#include "behaviour_control/ds_ctrl.h"
#include "systems/systems.h"

#include "vars.h" 

#define LINE_THRESH 90
#define EXTIME 200
#define LINES_EXIT_SPD 350

class LineSys2019 : public LineSystem{

    public:
        LineSys2019();
        LineSys2019(vector<DataSource*> in_, vector<DataSource*> out);

        void update() override;
        void test() override;
        void outOfBounds();
        
    private:
        vector<DataSource*> in, out;
        DataSource* ds;
        bool fboundsX, fboundsY, fboundsOX, fboundsOY, slow;
        int inV, outV, linesensOldX, linesensOldY, value, linetriggerI[4], linetriggerO[4], i;
        elapsedMillis exitTimer;
        int outDir, outVel;
        byte linesens;
};