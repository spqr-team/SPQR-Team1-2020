#define SENSORS_CPP
#include "sensors/sensors.h"

void initSensors(){
    pinMode(SWITCH_1, INPUT);
    pinMode(SWITCH_2, INPUT);
    
    drive = new DriveController(new Motor(12, 11, 4, 55), new  Motor(25, 24, 5, 135), new Motor(27, 26, 2, 225), new Motor(29, 28, 3, 305));
        //drive = new DriveController(new Motor(12, 11, 2, 45),new  Motor(25, 24, 5, 135), new Motor(27, 26, 6, 225), new Motor(21, 22, 23, 315));
    compass = new DataSourceBNO055();
    ball = new DataSourceBall(&Serial2, 57600);
    //ball = new DataSourceBall(&Serial4, 57600);
    camera = new DataSourceCameraConic(&Serial3, 19200);
    //camera = new DataSourceCameraConic(&Serial2, 19200);
    bt = new DataSourceBT(&Serial1, 115200);
    //bt = new DataSourceBT(&Serial3, 115200);
 }

void updateSensors(){
    role = digitalRead(SWITCH_1);
    camera->goalOrientation = digitalRead(SWITCH_2);
    
    compass->update();
    ball->update();
    camera->update();
}