#pragma once
#define startp 105
#define endp 115
//#define unkn 0b01101001 
#include "data_source.h"

class DataSourceCamera : public DataSource{

    public:
        DataSourceCamera(HardwareSerial* ser, int baud);
        void postProcess() override;
        void test() override;
        int fixCamIMU(int);
        void readSensor() override;
        int getValueAtk(bool);
        int getValueDef(bool);

        int count = 0, unkn_counter;
        byte xb, yb, xy, yy, true_xb, true_xy, true_yb, true_yy;
        bool data_received = false, start = false, end = false;

        int goalOrientation, pAtk, pDef, imuOff, portx, valX, valY, valB, oldGoalX, oldGoalY, oldGoalB;
        int cameraReady;
        int value;
        int startpY = 0;
        int startpB = 0;
        int endpY = 0; 
        int endpB = 0;
        int datavalid = 0;
        String valStringY = ""; 
        String valStringB = "";
        bool negateB, negateY; 
};