#include "misc.h"

float MISC::updatePID() {
  delta = imu.getEuler();
  if(delta > 180) delta = delta-360;
  delta = delta /*-st*/;

  errorP = KP * delta;

  errorD = KD * (delta - errorPre);
  errorPre = delta;

  integral = 0.5 * integral + delta;
  errorI = KI * integral;

  return errorD + errorP + errorI;
}

// calculates sins of integer angles from 0 to 359
void MISC::initSinCos() { 
  for (int i = 0; i < 360; i++) {
    sins[i] = sin(i * 3.14 / 180);
  }
  for (int i = 0; i < 360; i++) {
    cosin[i] = cos(i * 3.14 / 180);;
  }
}