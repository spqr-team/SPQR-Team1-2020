#pragma once

#include "behaviour_control/data_source.h"

class DataSourceCameraVShaped : public DataSource{

    public:
        DataSourceCameraVShaped(HardwareSerial* ser, int baud);
        void postProcess() override;
        void test() override;
        int fixCamIMU(int);
        void readSensor() override;
        // int getValueAtk(bool);
        // int getValueDef(bool);
        
        int goalOrientation, pAtk, pDef, imuOff, portx, valX, valY, valB, oldGoalX, oldGoalY, oldGoalB;
        int cameraReady;
        char value;
        int startpY = 0;
        int startpB = 0;
        int endpY = 0; 
        int endpB = 0;
        int datavalid = 0;
        String valStringY = ""; 
        String valStringB = "";
        bool negateB, negateY;
};