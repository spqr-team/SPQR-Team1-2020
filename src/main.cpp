#include <Arduino.h>
#include "drive.h"

DRIVE robot;

int angolo;


void setup() {
  DEBUG_PRINT.begin(9600);
  robot.initDrive();
}

void loop() {
  globalDir = 0;
  globalSpeed = 150;
  robot.drivePID(globalDir, globalSpeed);
}