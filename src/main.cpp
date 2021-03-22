#include <Arduino.h>

#define VARS

#include "behaviour_control/status_vector.h"
#include "sensors/sensors.h"
#include "strategy_roles/games.h"
#include "vars.h"
#include "test_menu.h"

TestMenu* testmenu;

bool striker_condition = false;
bool keeper_condition = false;

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

  //Startup sound
  tone(BUZZER, 220.00, 250);
}


void loop() {
  updateSensors();
  if(DEBUG.available()) testmenu->testMenu();
  
  striker_condition = role == HIGH || ((Keeper*)keeper)->shouldStrike;
  keeper_condition = role == LOW;

  striker->play(striker_condition);
  keeper->play(keeper_condition);

  // Last thing to do: movement and update status vector
  drive->drivePrepared();  
  updateStatusVector();
}