#pragma once

#include <Arduino.h>

class Motor {

    public:
        Motor(int a, int b, int pwm, int angle);
        Motor();
        void drive(int speed);
        void test();
    
    public:
        int pinA, pinB, pinPwm, angle;

};