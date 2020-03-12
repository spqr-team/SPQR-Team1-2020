#include <Arduino.h>

#include "test_menu.h"
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
/*   TestMenu testmenu;
  testmenu.testMenu();
  goalie->play(role==1);
  keeper->play(role==0);
<<<<<<< HEAD
 */
drive->m1->test();
=======

  camera->test();

>>>>>>> 4cd4b8f9d6012a435a9d2e4f1e1983a0adf3475e
  // Last thing to do: movement and update status vector
  drive->drivePrepared();  
  updateStatusVector();
} 
