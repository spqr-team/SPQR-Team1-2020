#include "data_source_bno055.h"

//bool loaded = false;

DataSourceBNO055::DataSourceBNO055(){
  protocol = P_I2C;
  
  bno = Adafruit_BNO055();
  bno.begin(bno.OPERATION_MODE_IMUPLUS);  //Posizione impostata a P7 alle righe 105,107 di Adafruit_BNO55.cpp
  bno.setExtCrystalUse(true);
  //loaded = true;
  value = 0;
  lastTime = 0;
}

void DataSourceBNO055::readSensor(){
  if(millis() - lastTime > DATA_CLOCK){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    this->value = (int) euler.x();
    lastTime = millis();
  }
}
