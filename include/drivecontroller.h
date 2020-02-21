#pragma once

#include <Arduino.h>
#include "motor.h"
#include "PID_v2.h"

//PID Constants
#define KP 1.5
#define KI 0.2
#define KD 0.1

#define KSPD 0.3

//BEST NUMBERS YET
//USE MOVING AVERAGE AND ANGLE WRAP
// #define KP 1.5
// #define KI 0
// #define KD 0.1

#define UNLOCK_THRESH 800

class DriveController{

    public:

        DriveController(Motor* m1_, Motor* m2_, Motor* m3_, Motor* m4_);
        
        void drive(int dir=0, int speed=0, int tilt=0);
        void prepareDrive(int dir, int speed, int tilt=0);
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
        int pDir, pSpeed, pTilt, oldSpeed;
        float x, y, vx, vy, speed1, speed2, speed3, speed4, pidfactor, delta;

        double input, output, setpoint;
        
        float sins[360], cosins[360];

};