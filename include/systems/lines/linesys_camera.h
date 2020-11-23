#pragma once

#include <Arduino.h>

#include "behaviour_control/ds_ctrl.h"
#include "systems/systems.h"

#include "vars.h" 

#define S1I 21 //A14 N
#define S1O 20 //A15
#define S2I 17 //A16 E
#define S2O 16 //A17
#define S3I 15 //A20 S
#define S3O 14 //A0
#define S4I 23 //A1  O
#define S4O 22 //A2

#define LINE_THRESH_CAM 90
#define EXIT_TIME 125
#define LINES_EXIT_SPD 350

class LineSysCamera : public LineSystem{

    public:
        LineSysCamera();
        LineSysCamera(vector<DataSource*> in_, vector<DataSource*> out);

        void update() override;
        void test() override;
        void outOfBounds();
        void checkLineSensors();
        
    private:
        vector<DataSource*> in, out;
        DataSource* ds;
        bool fboundsX, fboundsY, fboundsOX, fboundsOY, slow;
        int inV, outV, linesensOldX, linesensOldY, value, linetriggerI[4], linetriggerO[4], linepins[4], i;
        elapsedMillis exitTimer;
        int outDir, outVel;
        byte linesens;
};