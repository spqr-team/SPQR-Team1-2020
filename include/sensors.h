#pragma once


#ifdef SENSORS_CPP
#define s_extr 
#else
#define s_extr extern
#endif

#include <Arduino.h>
#include "data_source_bno055.h"
#include "data_source_ball.h"
#include "data_source_camera_conicmirror.h"
#include "data_source_camera_vshapedmirror.h"
#include "data_source_us.h"
#include "motor.h"
#include "ds_ctrl.h"
#include "drivecontroller.h"
#include "data_source_bt.h"
#include "systems.h"
#include "linesys_2019.h"
#include "positionsys_zone.h"

void initSensors();
void updateSensors();

s_extr vector<DataSource*> dUs;

s_extr DataSourceCtrl* usCtrl;
s_extr LineSys2019* linesCtrl;

s_extr DataSourceBNO055* compass;
s_extr DataSourceBall* ball;
s_extr DataSourceCameraVShaped* camera;
s_extr DriveController* drive;
s_extr DataSourceBT* bt;

s_extr int role;