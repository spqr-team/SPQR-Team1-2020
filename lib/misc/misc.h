#include <Arduino.h>
#include "vars.h"
#include "imu.h"

class TOPOLINO {
    public:
        float updatePID();
        void initSinCos();
        void initCompass();
    public:
        IMU imu;
    public:
        #define KP 2
        #define KD 1.7
        #define KI 0.1

        float errorP, errorD, errorI, errorPre;
        float delta;
        float integral;
        int st;
};