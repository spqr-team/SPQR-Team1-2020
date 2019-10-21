#include "motor.h"

Motor::Motor(int a, int b, byte pwm){
    pinA = a;
    pinB = b;
    pinPwm = pwm;
}

void Motor::drive(int dir, int speed){
    
}