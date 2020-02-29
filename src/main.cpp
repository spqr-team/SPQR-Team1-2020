#include <Arduino.h>

#include "behaviour_control/status_vector.h"
#include "position/positionsys_zone.h"
#include "sensors/sensors.h"
#include "strategy_roles/games.h"

void setup() {
  delay(1500);

  DEBUG.begin(9600);
  initStatusVector();
  initSensors();
  initGames();
  
  delay(500);
}


void loop() {
  updateSensors();

  goalie->play(role==1);
  keeper->play(role==0);  

  // Last thing to do: movement and update status vector
  drive->drivePrepared();  
  updateStatusVector();
} 
