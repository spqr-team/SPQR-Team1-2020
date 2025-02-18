#pragma once

#include <Arduino.h>

#include "behaviour_control/ds_ctrl.h"
#include "systems/systems.h"

#include "vars.h" 

#define S1O A7
#define S1I A6
#define S2O A2
#define S2I A3
#define S3I A9
#define S3O A8
#define S4I A0
#define S4O A1

#define LINE_THRESH_CAM_REC 350
#define EXIT_TIME_REC 300

#define X_LIMIT 4
#define Y_LIMIT 5

class LineSysCameraRecovery : public LineSystem{

    public:
        LineSysCameraRecovery();
        LineSysCameraRecovery(vector<DataSource*> in_, vector<DataSource*> out);

        void update() override;
        void test() override;
        void outOfBounds();
        void checkLineSensors();
        void striker();

        bool isInLimitX();
        bool isInLimitY();
        
    private:
        vector<DataSource*> in, out;
        DataSource* ds;
        bool fboundsX, fboundsY, fboundsOX, fboundsOY, slow;
        int inV, outV, linesensOldX, linesensOldY, value, linetriggerI[4], linetriggerO[4], linepins[4], i;
        unsigned long exitTimer;
        int outDir, outVel;
        byte linesens;
        int outX, outY;
};