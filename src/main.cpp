#include <Arduino.h>

#define VARS

#include "behaviour_control/status_vector.h"
#include "sensors/sensors.h"
#include "strategy_roles/games.h"
#include "vars.h"
#include "test_menu.h"

TestMenu* testmenu;

void setup() {
  delay(1500);
  DEBUG.begin(9600);
    
  for(int i = 0; i < 360; i++){
      sins[i] = (float) sin((i*3.14/180));
      cosins[i] =  (float) cos((i*3.14/180));
  }

  testmenu = new TestMenu();
  initStatusVector();
  initSensors();
  initGames();
  
  delay(500);

  drive->prepareDrive(0,0,0);
}


void loop() {
  updateSensors();
  if(DEBUG.available()) testmenu->testMenu();
  
  striker_test->play(1);
  // striker->play(role==1);
  // keeper->play(role==0);

  // drive->prepareDrive(0,0,0);

  // Last thing to do: movement and update status vector
  drive->drivePrepared();  
  updateStatusVector();
}