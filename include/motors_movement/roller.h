#pragma once

#include "ESC.h"

#define ROLLER_DEFAULT_SPEED 1200

class Roller{
    public:
        Roller(int pinPwm_, int pinSense, int MIN_, int MAX_, int ARM_);
        void setup();
        void speed(int);
        void update();
        
    public:
        ESC* roller;
        int pinPwm, pinSense, MIN, MAX, ARM;
        bool roller_arm_setup, roller_armed;

        int roller_setup_phase, roller_counter, roller_speed;
};