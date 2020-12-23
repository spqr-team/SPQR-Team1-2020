#include "systems/systems.h"
#include "vars.h"
#include "sensors/sensors.h"
#include <Arduino.h>

LineSystemEmpty::LineSystemEmpty(){
}

void LineSystemEmpty::update(){
    tookLine = false;
}
void LineSystemEmpty::test(){
    DEBUG.println("Empty LineSystem ready!");
}