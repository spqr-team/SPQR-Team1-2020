#pragma once


#ifdef SENSORS_CPP
#define s_extr 
#else
#define s_extr extern
#endif

#include <Arduino.h>
#include "data_source_bno055.h"
#include "data_source_ball.h"
#include "data_source_camera.h"
#include "data_source_us.h"
#include "ds_ctrl_lines.h"
#include "motor.h"
#include "ds_ctrl.h"
#include "drivecontroller.h"
#include "data_source_bt.h"

void initSensors();
void updateSensors();

s_extr vector<DataSource*> lIn;
s_extr vector<DataSource*> lOut;
s_extr vector<DataSource*> dUs;

s_extr DataSourceCtrl* usCtrl;
s_extr DSCtrlLines* linesCtrl;

s_extr DataSourceBNO055* compass;
s_extr DataSourceBall* ball;
s_extr DataSourceCamera* camera;
s_extr DriveController* drive;
s_extr DataSourceBT* bt;

s_extr int role;