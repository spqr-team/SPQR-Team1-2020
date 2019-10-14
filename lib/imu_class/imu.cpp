#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include "imu.h"

Adafruit_BNO055 bno = Adafruit_BNO055();


void IMU::initIMU() {
  bno.begin(bno.OPERATION_MODE_IMUPLUS);  //Posizione impostata a P7 alle righe 105,107 di Adafruit_BNO55.cpp
  bno.setExtCrystalUse(true);
}

float IMU::getEuler() {

}



void IMU::getData() {

}