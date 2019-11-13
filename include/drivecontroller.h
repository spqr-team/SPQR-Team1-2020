#pragma once

#include <Arduino.h>
#include "motor.h"

//PID Constants
#define KP 0.7
#define KI 0 
#define KD 0.7
#define DEADZONE_MIN 25

class DriveController{

    public:

        DriveController(Motor* m1_, Motor* m2_, Motor* m3_, Motor* m4_);
        
        void drive(int dir, int speed, int tilt);
        void prepareDrive(int dir, int speed, int tilt);
        void drivePrepared();
        float updatePid();

    private:
        Motor* m1;
        Motor* m2;
        Motor* m3;
        Motor* m4;
        int pDir, pSpeed, pTilt;
        float speed1, speed2, speed3, speed4, errorePre, integral, pidfactor, errorP, errorD, errorI, delta;
        int vx, vy;
        
        float sins[360], cosins[360];

};