#include <Arduino.h>
#include "vars.h"
#include "imu.h"

class MISC {
    public:
        float updatePID();
        void initSinCos();
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