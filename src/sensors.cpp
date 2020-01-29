#define SENSORS_CPP
#include "sensors.h"

void initSensors(){
    pinMode(SWITCH_DX, INPUT);
    pinMode(SWITCH_SX, INPUT);

    pinMode(LED_R, OUTPUT);
    pinMode(LED_Y, OUTPUT);
    pinMode(LED_G, OUTPUT);

    dUs = { new DataSourceUS(&Wire1, int(112)), new DataSourceUS(&Wire1, int(113)), 
    new DataSourceUS(&Wire1, int(114)), new DataSourceUS(&Wire1, int(115)) };

    drive = new DriveController(new Motor(12, 11, 2, 45),new  Motor(25, 24, 5, 135), new Motor(27, 26, 6, 225), new Motor(21, 22, 23, 315));
    compass = new DataSourceBNO055();
    ball = new DataSourceBall(&Serial4, 57600);
    camera = new DataSourceCameraVShaped(&Serial2, 19200);
    usCtrl = new DataSourceCtrl(dUs);
    bt = new DataSourceBT(&Serial3, 115200);
 }

void updateSensors(){
    role = digitalRead(SWITCH_DX);
    camera->goalOrientation = digitalRead(SWITCH_SX);
    
    compass->update();
    ball->update();
    camera->update();
    usCtrl->update();
}