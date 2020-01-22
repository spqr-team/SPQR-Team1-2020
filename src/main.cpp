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
<<<<<<< HEAD
  //camera->test();
  goalie->play(role==1);
  keeper->play(role==0);  

  ball->test();


  // Last thing to do: movement  
  drive->drivePrepared();  
=======
  
  // goalie->play(role==1);
  // keeper->play(role==0);

  // Last thing to do: movement  
  // drive->drivePrepared(); 
  //Serial.print("ao");
  camera->test();
>>>>>>> d534c5b4a8c2064cb43c42f9269b7f0256894ef8
} 
