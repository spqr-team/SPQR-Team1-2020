#include "data_source_ball.h"
#include "vars.h"

DataSourceBall :: DataSourceBall(HardwareSerial* ser_, int baud) : DataSource(ser_, baud) {
  ballSeen = false;
  distance = 0;
  angle = 0;
}

void DataSourceBall :: postProcess(){
    if((value & 0x01) == 1){
        distance = value;
        ballSeen = distance > 1;
      }else{ 
        angle = value * 2; 
      }
}

void DataSourceBall :: test(){
    this->update();
    if(ballSeen){
    DEBUG.print(angle); 
    DEBUG.print(" | ");
    DEBUG.println(distance); 
    }else{
    DEBUG.println("Not seeing ball");
    }
}