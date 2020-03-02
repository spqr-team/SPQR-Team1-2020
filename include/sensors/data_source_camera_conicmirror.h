#pragma once

#include "behaviour_control/data_source.h"

#define startp 105
#define endp 115
#define unkn 116
//Coords are mapped from 0 up to this value
#define MAP_MAX 100
#define HALF_MAP_MAX  50

class DataSourceCameraConic : public DataSource{

    public:
        DataSourceCameraConic(HardwareSerial* ser, int baud);
        void test() override;
        void readSensor() override;
        // int getValueAtk(bool);
        // int getValueDef(bool);

        int yAngle, bAngle, yAngleFix, bAngleFix, yDist, bDist;

        int count = 0, unkn_counter;
        int xb, yb, xy, yy, true_xb, true_xy, true_yb, true_yy, calc_xb, calc_yb, calc_xy, calc_yy, true_xb_fixed,
            true_xy_fixed, true_yb_fixed, true_yy_fixed;
        bool data_received = false, start = false, end = false;

        int goalOrientation, pAtk, pDef;
        int value;
};