#pragma once

#include <Arduino.h>

class Motor {

    public:
        Motor(int a, int b, int pwm, int angle);
        void drive(int speed);
    
    public:
        int pinA, pinB, pinPwm, angle;

};