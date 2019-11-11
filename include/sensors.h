#include <Arduino.h>
#include "data_source_bno055.h"
#include "motor.h"
#include "drivecontroller.h"

#ifdef SENSORS_CPP
#define extr 
#else
#define extr extern
#endif

void initSensors();
void updateSensors();

extr DataSourceBNO055* compass;
extr DriveController* drive;