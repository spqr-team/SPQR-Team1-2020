#include <Arduino.h>
#include "motor.h"
#include "misc.h"

class DRIVE {
    public:
        void initDrive();
        void recenter(float);
        void drivePID(signed int, float);
        void preparePID(signed int,int);
        void preparePID(signed int, int, int);

    public:
        MOTOR mot1;
        MOTOR mot2;
        MOTOR mot3;
        MOTOR mot4;
        MOTOR m; //for init

        MISC misc;

    public:
        float vx, vy;
        float speed1, speed2, speed3, speed4;
        float pidfactor;
        int prevPidDir, prevPidSpeed;
        
};