#include <Arduino.h>
#include "data_source_bno055.h"
#include "data_source_ball.h"
#include "data_source_camera.h"
#include "data_source_us.h"
#include "ds_ctrl_lines.h"
#include "motor.h"
#include "ds_ctrl.h"
#include "drivecontroller.h"

#ifdef SENSORS_CPP
#define extr 
#else
#define extr extern
#endif

void initSensors();
void updateSensors();

extr DataSource* compass;
extr DataSource* ball;
extr DataSource* camera;
extr DataSourceCtrl* usCtrl;
extr DataSourceCtrlLines* linesCtrl;
extr DriveController* drive;

extr vector<DataSource*> lIn;
extr vector<DataSource*> lOut;
extr vector<DataSource*> dUs;
