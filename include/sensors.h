#include <Arduino.h>
#include "data_source_bno055.h"
#include "data_source_ball.h"
#include "data_source_camera.h"
#include "motor.h"
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
extr DriveController* drive;
