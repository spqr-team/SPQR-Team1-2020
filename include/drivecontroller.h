#pragma once

#include <Arduino.h>
#include "motor.h"
#include "PID_v1.h"

//PID Constants
#define KP 1.2
#define KI 0.0
#define KD 0.25

#define UNLOCK_THRESH 800

class DriveController{

    public:

        DriveController(Motor* m1_, Motor* m2_, Motor* m3_, Motor* m4_);
        
        void drive(int dir=0, int speed=0, int tilt=0);
        void prepareDrive(int dir, int speed, int tilt);
        void prepareDrive(int dir, int speed);
        void drivePrepared();
        float updatePid();
        float torad(float f);

        int vxp, vyp, vxn, vyn;
        bool canUnlock;
        unsigned long unlockTime;

    private:
        Motor* m1;
        Motor* m2;
        Motor* m3;
        Motor* m4;
        PID* pid;
        int pDir, pSpeed, pTilt;
        int gDir, gSpeed, gTilt;
        int speed1, speed2, speed3, speed4, errorePre, integral, pidfactor, errorP, errorD, errorI, delta;
        double input, output, setpoint;
        int vx, vy;
        
        float sins[360], cosins[360];

};