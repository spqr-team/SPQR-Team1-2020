// #pragma once

// #include <Arduino.h>

// #include "behaviour_control/ds_ctrl.h"
// #include "position/systems.h"

// #include "vars.h" 

// #define S1I A14
// #define S1O A15
// #define S2I A16
// #define S2O A17
// #define S3I A20
// #define S3O A0
// #define S4I A1
// #define S4O A2

// #define LINE_THRESH_CAM 90
// #define EXTIME_CAM 75
// #define LINES_EXIT_SPD_CAM 300

// class LineSysCamera : public LineSystem{

//     public:
//         LineSysCamera();
//         LineSysCamera(vector<DataSource*> in_, vector<DataSource*> out);

//         void update() override;
//         void test() override;
//         void outOfBounds();
        
//     private:
//         vector<DataSource*> in, out;
//         DataSource* ds;
//         bool fboundsX, fboundsY, fboundsOX, fboundsOY, slow;
//         int inV, outV, linesensOldX, linesensOldY, value, linetriggerI[4], linetriggerO[4], i;
//         unsigned long exitTimer;
//         byte linesens;
// };