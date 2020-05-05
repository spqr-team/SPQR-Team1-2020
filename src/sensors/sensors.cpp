#define SENSORS_CPP
#include "sensors/sensors.h"

void initSensors(){
    pinMode(SWITCH_DX, INPUT);
    pinMode(SWITCH_SX, INPUT);

    pinMode(LED_R, OUTPUT);
    pinMode(LED_Y, OUTPUT);
    pinMode(LED_G, OUTPUT);
  
    drive = new DriveController(new Motor(11, 12, 4, 45),new  Motor(24, 25, 5, 135), new Motor(26, 27, 2, 225), new Motor(28, 29, 3, 315));
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
    role = digitalRead(SWITCH_DX);
    camera->goalOrientation = digitalRead(SWITCH_SX);
    
    compass->update();
    ball->update();
    camera->update();
    usCtrl->update();
}