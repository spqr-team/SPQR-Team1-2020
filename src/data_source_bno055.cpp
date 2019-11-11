#include "data_source_bno055.h"

//bool loaded = false;

DataSourceBNO055::DataSourceBNO055(){
    bno = Adafruit_BNO055();
    bno.begin(bno.OPERATION_MODE_IMUPLUS);  //Posizione impostata a P7 alle righe 105,107 di Adafruit_BNO55.cpp
    bno.setExtCrystalUse(true);
    //loaded = true;
    value = 0;
}

void DataSourceBNO055::readSensor(){
// if(loaded){
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  value = (int) euler.x();
//  }
}
