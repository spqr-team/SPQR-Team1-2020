#include <Arduino.h>

#include "game.h"

void setup() {
  delay(500);

  DEBUG.begin(9600);
  initSensors();
  delay(2000);
}


void loop() {
  updateSensors();
  
  goalie->goalie();
  linesCtrl->update();

  // Last thing to do: movement  
  drive->drivePrepared();
} 
