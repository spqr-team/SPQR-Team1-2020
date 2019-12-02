#include <Arduino.h>
#include "data_source_bno055.h"
#include "data_source_ball.h"
#include "data_source_camera.h"
#include "data_source_us.h"
#include "motor.h"
#include "data_source_controller.h"
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
//extr DataSource* us;
extr DataSourceController* usCtrl;
extr DriveController* drive;
