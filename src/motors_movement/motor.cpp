#include "motors_movement/motor.h"
#include "vars.h"
#include <Arduino.h>

Motor::Motor(int a, int b, int pwm, int angle_){
    this->pinA = a;
    this->pinB = b;
    this->pinPwm = pwm;
    this->angle = angle_;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
    analogWriteFrequency(pinPwm, 5000);
}

Motor::Motor(){ }

void Motor::drive(int speed){
    byte VAL_INA, VAL_INB;
    if (speed == 0) {
        // no brake ma motore inerte corto a massa e vel=0 contro freno
        // dove corto a VCC e vel=max
        VAL_INA = 0;
        VAL_INB = 0;
    } else if (speed > 0) {
        // clockwise
        VAL_INA = 1;
        VAL_INB = 0;
    } else if (speed < 0) {
        // counterclockwise
        VAL_INA = 0;
        VAL_INB = 1;
        speed *= -1;
    }
    digitalWrite(pinA, VAL_INA);
    digitalWrite(pinB, VAL_INB);
    analogWrite(pinPwm, speed);
}

void Motor::test(){
    digitalWrite(pinA, 0);
    digitalWrite(pinB, 1);
    analogWrite(pinPwm, 255);
    delay(1500);

    digitalWrite(pinA, 1);
    digitalWrite(pinB, 0);
    analogWrite(pinPwm, 255);
    delay(1500);

}