#include <Arduino.h>

#include "game.h"


void setup() {
  delay(1000);

  DEBUG_PRINT.begin(9600);
  
  initSensors();
}

void loop() {
  updateSensors();
  /*if(millis() % 100 == 0)
  DEBUG_PRINT.println(us->getValue());*/
 /*  game->role = digitalRead(SWITCH_DX);
  game->attackGoal = digitalRead(SWITCH_SX);
  if(game->role) goalie->goalie();
  else keeper->keeper(); */
  goalie->goalie();
  //drive->drivePrepared();
  //compass->test();
  //usCtrl->test();
}