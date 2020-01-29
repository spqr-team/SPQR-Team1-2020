#include <Arduino.h>

#include "sensors.h"
#include "games.h"

void setup() {
  delay(1000);

  DEBUG.begin(9600);
  initSensors();
  initGames();
  
  delay(2000);
}


void loop() {
  updateSensors();
  // camera->test();
  goalie->play(role==1);
  keeper->play(role==0);  

  // Last thing to do: movement  
  drive->drivePrepared();  
} 
