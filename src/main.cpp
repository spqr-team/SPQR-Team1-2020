#include <Arduino.h>
#include "vars.h"
#include "data_source_bno055.h"
#include "drivecontroller.h"
#include "sensors.h"


void setup() {
  DEBUG_PRINT.begin(9600);
  initSensors();
}

void loop() {
  updateSensors();

  //should recenter using predefined values
  drive->drive();
}