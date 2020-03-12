#include <Arduino.h>

#define VARS

#include "behaviour_control/status_vector.h"
#include "position/positionsys_zone.h"
#include "sensors/sensors.h"
#include "strategy_roles/games.h"
#include "vars.h"

void setup() {
  delay(1500);
  DEBUG.begin(9600);
    
  for(int i = 0; i < 360; i++){
      sins[i] = (float) sin((i*3.14/180));
      cosins[i] =  (float) cos((i*3.14/180));
  }

  initStatusVector();
  initSensors();
  initGames();
  
  delay(500);
}


void loop() {
  updateSensors();

  goalie->play(role==1);
  keeper->play(role==0);

  camera->test();

  // Last thing to do: movement and update status vector
  drive->drivePrepared();  
  updateStatusVector();
} 
