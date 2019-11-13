#define SENSORS_CPP
#include "sensors.h"

void initSensors(){
    compass = new DataSourceBNO055();
    drive = new DriveController(new Motor(12, 11, 2, 45),new  Motor(25, 24, 5, 135), new Motor(27, 26, 6, 225), new Motor(21, 22, 23, 315));
}

void updateSensors(){
    compass->readSensor();
}