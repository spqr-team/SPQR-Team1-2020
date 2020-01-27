#pragma once
#define startp 105
#define endp 115
//Coords are mapped from 0 up to this value
#define MAP_MAX 100
#define HALF_MAP_MAX  50
//#define unkn 0b01101001 
#include "data_source.h"

class DataSourceCamera : public DataSource{

    public:
        DataSourceCamera(HardwareSerial* ser, int baud);
        void test() override;
        void readSensor() override;
        int getValueAtk(bool);
        int getValueDef(bool);

        int yAngle, bAngle, yAngleFix, bAngleFix, yDist, bDist;

        int count = 0, unkn_counter;
        byte xb, yb, xy, yy, true_xb, true_xy, true_yb, true_yy, calc_xb, calc_yb, calc_xy, calc_yy;
        bool data_received = false, start = false, end = false;

        int goalOrientation, pAtk, pDef;
        int value;
};