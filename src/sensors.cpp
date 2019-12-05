#define SENSORS_CPP
#include "sensors.h"

void initSensors(){
    pinMode(SWITCH_DX, INPUT);
    pinMode(SWITCH_SX, INPUT);

    dUs = { new DataSourceUS(&Wire1, int(112)), new DataSourceUS(&Wire1, int(113)), 
    new DataSourceUS(&Wire1, int(114)), new DataSourceUS(&Wire1, int(115)) };

    lIn = { new DataSource(S1I, true), new DataSource(S2I, true), new DataSource(S3I, true), new DataSource(S4I, true) };
    lOut = { new DataSource(S1O, true), new DataSource(S2O, true), new DataSource(S3O, true), new DataSource(S4O, true) };

    drive = new DriveController(new Motor(12, 11, 2, 45),new  Motor(25, 24, 5, 135), new Motor(27, 26, 6, 225), new Motor(21, 22, 23, 315));
    compass = new DataSourceBNO055();
    ball = new DataSourceBall(&Serial4, 57600);
    camera = new DataSourceCamera(&Serial2, 19200);
    usCtrl = new DataSourceCtrl(dUs);
    linesCtrl = new DataSourceCtrlLines(lIn, lOut);

    game = new Game();
    goalie = new Goalie();
    keeper = new Keeper();
}

void updateSensors(){
    compass->update();
    ball->update();
    camera->update();
    usCtrl->update();
}