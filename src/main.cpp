#include <Arduino.h>
#include "vars.h"
#include "data_source_bno055.h"
// #include <imu_class/imu.cpp>
//cyao c:

DataSourceBNO055* compass;

void setup() {
  DEBUG_PRINT.begin(9600);
  compass = new DataSourceBNO055();
}

void loop() {
  compass->readSensor();
  DEBUG_PRINT.println(compass->getValue());

  //DEBUG_PRINT.println("Ciaooo");
  delay(100);
}