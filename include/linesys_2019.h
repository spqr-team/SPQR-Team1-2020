#pragma once

#include "ds_ctrl.h"
#include "systems.h"
#include "vars.h" 
#include <Arduino.h>

#define S1I A14
#define S1O A15
#define S2I A16
#define S2O A17
#define S3I A20
#define S3O A0
#define S4I A1
#define S4O A2

#define LINE_THRESH 90
#define EXTIME 100
#define LINES_EXIT_SPD 350

class LineSys2019 : public LineSystem{

    public:
        LineSys2019();
        LineSys2019(vector<DataSource*> in_, vector<DataSource*> out);

        void update() override;
        void test() override;
        void outOfBounds();
        void handleIntern();
        void handleExtern();
        
    private:
        vector<DataSource*> in, out;
        DataSource* ds;
        bool fboundsX, fboundsY, fboundsOX, fboundsOY, slow;
        int inV, outV, linesensOldX, linesensOldY, value, linetriggerI[4], linetriggerO[4], i;
        elapsedMillis exitTimer;
        byte outDir, outVel, linesens;
        unsigned long unlockTime;
};