#pragma once

#include <Arduino.h>
#include "behaviour_control/complementary_filter.h"

#define DRIVE_DURATION_MS 5

class Motor {

    public:
        Motor(int a, int b, int pwm, int angle);
        Motor();
        void drive(int speed);
        void test();
        void stop();

    public:
        int angle;

    private:
        int pinA, pinB, pinPwm;
        ComplementaryFilter* filter;
};