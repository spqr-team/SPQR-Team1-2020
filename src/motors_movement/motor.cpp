#include "motors_movement/motor.h"
#include "vars.h"
#include <Arduino.h>

Motor::Motor(int a, int b, int pwm, int angle_){
    this->pinA = a;
    this->pinB = b;
    this->pinPwm = pwm;
    this->angle = angle_;
    this->oldSpeed = 0;
    this->diff = 0;
    this->micros_wait = 0;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
    analogWriteFrequency(pinPwm, 15000);
}

Motor::Motor(){ }

void Motor::drive(int speed){

    // Create a smooth transitioning between the old and new speed value, to avoid the motor drivers going into overcurrent protection
    diff = abs(abs(speed) - abs(oldSpeed));

    if(diff < 10) return;

    micros_wait = (float)DRIVE_DURATION_MS/diff * 1000;
    float micros_wait_half = micros_wait * 0.5;
    
    if(oldSpeed > 0 && speed > 0){
        
        digitalWriteFast(pinA, HIGH);
        digitalWriteFast(pinB, LOW);

        if(oldSpeed < speed){
            // Ramp up 
            for(int i = oldSpeed; i < speed; i++){
                analogWrite(pinPwm, i);
            }
            
        } else if(oldSpeed > speed) {
            // Slow down
            for(int i = oldSpeed; i > speed; i--){
                analogWrite(pinPwm, i);
            }
        }

    }
    else if(oldSpeed < 0 && speed < 0){
        digitalWriteFast(pinA, LOW);
        digitalWriteFast(pinB, HIGH);

        if(oldSpeed < speed){
            // Ramp up 
            for(int i = oldSpeed; i < speed; i++){
                analogWrite(pinPwm, -i);
            }
            
        } else if(oldSpeed > speed) {
            // Slow down
            for(int i = oldSpeed; i > speed; i--){
                analogWrite(pinPwm, -i);
            }

        }

    }
    else if(oldSpeed < 0 && speed > 0){

        digitalWriteFast(pinA, LOW);
        digitalWriteFast(pinB, HIGH);

        for(int i = oldSpeed; i <= 0; i++){
            analogWrite(pinPwm, -i);
        }

        digitalWriteFast(pinA, LOW);
        digitalWriteFast(pinB, LOW);

        delayMicroseconds(micros_wait);

        digitalWriteFast(pinA, HIGH);
        digitalWriteFast(pinB, LOW);

        for(int i = 0; i < speed; i++){
            analogWrite(pinPwm, i);
        }

    }else if(oldSpeed > 0 && speed < 0){

        digitalWriteFast(pinA, HIGH);
        digitalWriteFast(pinB, LOW);

        for(int i = oldSpeed; i >= 0; i--){
            analogWrite(pinPwm, i);
            delayMicroseconds(micros_wait_half);
        }


        digitalWriteFast(pinA, LOW);
        digitalWriteFast(pinB, LOW);

        delayMicroseconds(micros_wait);

        digitalWriteFast(pinA, LOW);
        digitalWriteFast(pinB, HIGH);

        for(int i = 0; i > speed; i--){
            analogWrite(pinPwm, -i);
            delayMicroseconds(micros_wait_half);
        }

    }

    oldSpeed = speed;
}

void Motor::test(){
    digitalWriteFast(pinA, 0);
    digitalWriteFast(pinB, 1);
    analogWrite(pinPwm, 255);
    delay(1500);

    digitalWriteFast(pinA, 1);
    digitalWriteFast(pinB, 0);
    analogWrite(pinPwm, 255);
    delay(1500);

}