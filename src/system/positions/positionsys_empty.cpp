#include "systems/systems.h"
#include "vars.h"
#include "sensors/sensors.h"
#include <Arduino.h>

PositionSystemEmpty::PositionSystemEmpty(){
    
}

void PositionSystemEmpty::update(){
}

void PositionSystemEmpty::test(){
    DEBUG.println("Empty PositionSystemEmpty ready!");
}

void PositionSystemEmpty::goCenter(){
    drive->prepareDrive(0,0,0);
}

void PositionSystemEmpty::centerGoal(){
    drive->prepareDrive(0,0,0);
}
