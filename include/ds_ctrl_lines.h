#pragma once
#include "ds_ctrl.h"
#include "data_source.h"
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

class DSCtrlLines : public DataSourceCtrl {

    public:
        DSCtrlLines();
        DSCtrlLines(vector<DataSource*> in_, vector<DataSource*> out);

        void read() override;
        void postProcess() override;
        void outOfBounds();
        void handleIntern();
        void handleExtern();
        int getValue();
        void test() override;
        
    private:
        vector<DataSource*> in, out;
        DataSource* ds;
        bool fboundsX, fboundsY, fboundsOX, fboundsOY, slow;
        int inV, outV, inVOldX, inVOldY, value, linetriggerI[4], linetriggerO[4], i;
        elapsedMillis exitTimer;
        int outDir, outVel;
};