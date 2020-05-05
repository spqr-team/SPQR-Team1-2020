#pragma once

#include <Arduino.h>

#include "behaviour_control/ds_ctrl.h"
#include "position/systems.h"

#include "vars.h" 

#define S1I 21 //A14 N
#define S1O 20 //A15
#define S2I 17 //A16 E
#define S2O 16 //A17
#define S3I 15 //A20 S
#define S3O 14 //A0
#define S4I 23 //A1  O
#define S4O 22 //A2

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