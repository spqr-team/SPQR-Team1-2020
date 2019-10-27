#include "imu.h"
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055();

void IMU::initIMU() {
  bno.begin(bno.OPERATION_MODE_IMUPLUS);
  bno.setExtCrystalUse(true);
}

int IMU::getEuler() {
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  if (euler.x() != imu_current_euler) {
    imu_current_euler = euler.x();
  }
  return imu_current_euler;
}