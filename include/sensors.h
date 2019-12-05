#include <Arduino.h>
#pragma once
#include "data_source_bno055.h"
#include "data_source_ball.h"
#include "data_source_camera.h"
#include "data_source_us.h"
#include "motor.h"
#include "data_source_controller.h"
#include "drivecontroller.h"
#include "game.h"
#ifdef SENSORS_CPP
#define extr 
#else
#define extr extern
#endif

class Game;
class Goalie;
class Keeper;
void initSensors();
void updateSensors();

extr DataSourceBNO055* compass;
extr DataSourceBall* ball;
extr DataSourceCamera* camera;
//extr DataSource* us;
extr DataSourceController* usCtrl;
extr DriveController* drive;

extr Game* game;
extr Goalie* goalie;
extr Keeper* keeper;