#include "data_source_bno055.h"

DataSourceBN0O55::DataSourceBN0O55(){
  bno.begin(bno.OPERATION_MODE_IMUPLUS);  //Posizione impostata a P7 alle righe 105,107 di Adafruit_BNO55.cpp
  bno.setExtCrystalUse(true);
}

void DataSourceBN0O55::update(){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    if (euler.x() != value) {
      value = euler.x();
    }
  return;
}