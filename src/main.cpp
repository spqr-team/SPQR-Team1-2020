#include <Arduino.h>
#include "vars.h"
#include "data_source_bno055.h"
#include "drivecontroller.h"
#include "sensors.h"


void setup() {
  delay(1000);

  DEBUG_PRINT.begin(9600);
  
  initSensors();
}

void loop() {
  updateSensors();
  /*if(millis() % 100 == 0)
  DEBUG_PRINT.println(us->getValue());*/
}