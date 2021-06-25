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

#define LINE_THRESH_CAM 350
#define EXIT_TIME 300

class LineSysCameraRR : public LineSystem{

    public:
        LineSysCameraRR();
        LineSysCameraRR(vector<DataSource*> in_, vector<DataSource*> out);

        void update() override;
        void test() override;
        void outOfBounds();
        void checkLineSensors();
    
    public:
        bool tookLine = false, flag = false;
        int linetriggerI[4], linetriggerO[4];
        
    private:
        vector<DataSource*> in, out;
        DataSource* ds;
        int inV, outV, linesensOldX, linesensOldY, value, linepins[4], i;
};