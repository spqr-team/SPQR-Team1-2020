#include <Arduino.h>

#include "sensors.h"
#include "games.h"

void setup() {
  delay(500);

  DEBUG.begin(19600);
  initSensors();
  initGames();
  
  delay(2000);
}


void loop() {
  updateSensors();
  //camera->test();
  goalie->play(role==1);
  keeper->play(role==0);  


  camera->test();
  
  // Last thing to do: movement  
  drive->drivePrepared();  
} 
