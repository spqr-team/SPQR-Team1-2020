#pragma once

#include <Arduino.h>
#include "motor.h"

//PID Constants

#define KP 0.9
#define KI 0   
#define KD 0

class DriveController{

    public:

        DriveController(Motor* m1_, Motor* m2_, Motor* m3_, Motor* m4_);
        
        void drive(int dir=0, int speed=0, int tilt=0);
        void prepareDrive(int dir=0, int speed=0, int tilt=0);
        void drivePrepared();
        float updatePid();
        float torad(float f);

        int vxp, vyp, vxn, vyn;
        bool canUnlock;
        elapsedMillis unlockTime;

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