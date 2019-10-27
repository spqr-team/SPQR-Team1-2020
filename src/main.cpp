#include <Arduino.h>
#include "drive.h"

DRIVE robot;

int angolo;


void setup() {
  DEBUG_PRINT.begin(9600);
  robot.initDrive();
}

void loop() {
  robot.drivePID(0, 150);
}