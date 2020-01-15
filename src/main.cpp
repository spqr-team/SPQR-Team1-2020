#include <Arduino.h>

#include "sensors.h"
#include "games.h"

void setup() {
  delay(500);

  DEBUG.begin(9600);
  initSensors();
  initGames();
  
  delay(2000);
}


void loop() {
  updateSensors();
  
  goalie->play(role==1);
  keeper->play(role==0);

  // Last thing to do: movement  
  drive->drivePrepared(); 
} 
