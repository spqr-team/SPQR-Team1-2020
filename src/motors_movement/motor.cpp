#include "motors_movement/motor.h"
#include "vars.h"
#include <Arduino.h>

Motor::Motor(int a, int b, int pwm, int angle_){
    this->pinA = a;
    this->pinB = b;
    this->pinPwm = pwm;
    this->angle = angle_;

    filter = new ComplementaryFilter(0.8);

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
    analogWriteFrequency(pinPwm, 5000);
}

Motor::Motor(){ }

void Motor::drive(int speed){
    speed = filter->calculate(speed);

    if(speed > 0){
        digitalWriteFast(pinA, HIGH);
        digitalWriteFast(pinB, LOW);
    }else if(speed < 0){
        digitalWriteFast(pinA, LOW);
        digitalWriteFast(pinB, HIGH);
        speed *= -1;
    }else{
        digitalWriteFast(pinA, LOW);
        digitalWriteFast(pinB, LOW);
    }
    analogWrite(pinPwm, speed);
}

void Motor::stop(){
    this->drive(0);
}

void Motor::test(){
    digitalWriteFast(pinA, 0);
    digitalWriteFast(pinB, 1);
    analogWrite(pinPwm, 255);
    delay(1500);


    digitalWriteFast(pinA, 0);
    digitalWriteFast(pinB, 0);
    analogWrite(pinPwm, 0);
    delay(500);

    digitalWriteFast(pinA, 1);
    digitalWriteFast(pinB, 0);
    analogWrite(pinPwm, 255);
    delay(1500);

    digitalWriteFast(pinA, 0);
    digitalWriteFast(pinB, 0);
    analogWrite(pinPwm, 0);
    delay(500);

}