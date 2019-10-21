#include <Arduino.h>

class Motor {

    public:
        Motor(int a, int b, byte pwm);
        void drive(int dir, int speed);
    
    public:
        int pinA, pinB;
        byte pinPwm;

};