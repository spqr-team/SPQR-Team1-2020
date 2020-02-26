#include <Arduino.h>

#include "sensors.h"
#include "games.h"
#include "status_vector.h"
#include "positionsys_zone.h"

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
  // drive->prepareDrive(0,0,  CURRENT_DATA_READ.angleAtkFix);

  drive->drivePrepared();  
  updateStatusVector();
} 
