#define SENSORS_CPP
#include "sensors/sensors.h"

void initSensors(){
    pinMode(SWITCH_DX, INPUT);
    pinMode(SWITCH_SX, INPUT);
    pinMode(SWITCH_ID, INPUT);
    
    drive = new DriveController(new Motor(12, 11, 4, 55), new  Motor(25, 24, 5, 135), new Motor(27, 26, 2, 225), new Motor(29, 28, 3, 305));
    compass = new DataSourceBNO055();
    ball = new DataSourceBall(&Serial2, 57600);
    camera = new DataSourceCameraConic(&Serial3, 19200);
    bt = new DataSourceBT(&Serial1, 115200);
    roller = new Roller(30, 31, 1000, 2000, 500);
 }

void updateSensors(){
    role = digitalRead(SWITCH_DX);
    camera->old_goalOrientation = camera ->goalOrientation;
    camera->goalOrientation = digitalRead(SWITCH_SX);
    robot_indentifier = digitalRead(SWITCH_ID);
    
    compass->update();
    ball->update();
    camera->update();

    roller->update();
}