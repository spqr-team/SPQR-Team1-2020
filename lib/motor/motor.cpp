#include "motor.h"

void MOTOR::initMot(){
  pinMode(PWM_MOT[1], OUTPUT);
  pinMode(INA_MOT[1], OUTPUT);
  pinMode(INB_MOT[1], OUTPUT);
  pinMode(PWM_MOT[2], OUTPUT);
  pinMode(INA_MOT[2], OUTPUT);
  pinMode(INB_MOT[2], OUTPUT);
  pinMode(PWM_MOT[3], OUTPUT);
  pinMode(INA_MOT[3], OUTPUT);
  pinMode(INB_MOT[3], OUTPUT);
  pinMode(PWM_MOT[4], OUTPUT);
  pinMode(INA_MOT[4], OUTPUT);
  pinMode(INB_MOT[4], OUTPUT);
  analogWriteFrequency(2 , 15000);
  analogWriteFrequency(5 , 15000);
  analogWriteFrequency(6,  15000);
  analogWriteFrequency(23, 15000);
}

void MOTOR::mot(byte mot, int vel) {
    if (vel == 0) {
        VAL_INA = 0;
        VAL_INB = 0;
    } else if (vel > 0) {
        // clockwise
        VAL_INA = 1;
        VAL_INB = 0;
    } else if (vel < 0) {
        // counterclockwise
        VAL_INA = 0;
        VAL_INB = 1;
        vel = -vel;
    }
  digitalWrite(INA_MOT[mot], VAL_INA);
  digitalWrite(INB_MOT[mot], VAL_INB);
  analogWrite(PWM_MOT[mot], vel);
  return;
}
