#include <Arduino.h>
#include "drive.h"
#include "vars.h"

DRIVE robot;

int angolo;


void setup() {
  DEBUG_PRINT.begin(9600);
  robot.initDrive();
}

void loop() {
  robot.drivePID(globalDir, globalSpeed);
}