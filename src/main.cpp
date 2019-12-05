#include <Arduino.h>
#include "vars.h"
#include "data_source_bno055.h"
#include "drivecontroller.h"
#include "sensors.h"


void setup() {
  delay(500);

  DEBUG.begin(9600);
  initSensors();
  delay(2000);
}

void loop() {
  updateSensors();

  drive->prepareDrive(0,0,0);
  linesCtrl->update();
 
  drive->drivePrepared();

} 