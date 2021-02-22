#include "behaviour_control/status_vector.h"
#include "sensors/data_source_ball.h"
#include "vars.h"

DataSourceBall :: DataSourceBall(HardwareSerial* ser_, int baud) : DataSource(ser_, baud) {
  ballSeen = false;
  distance = 0;
  angle = 0;
}

void DataSourceBall :: postProcess(){
  if((value & 0x01) == 1){
      distance = value;
      ballSeen = distance == 255 ? 0 : 1;
  }else{ 
    angle = value * 2; 
  }
  CURRENT_INPUT_WRITE.ballByte = value;
  CURRENT_DATA_WRITE.ballAngle = angle;
  CURRENT_DATA_WRITE.ballDistance = distance;
  CURRENT_DATA_WRITE.ballSeen = ballSeen;
}

void DataSourceBall :: test(){
    this->update();
    // if(ballSeen){
    DEBUG.print(angle); 
    DEBUG.print(" | ");
    DEBUG.print(distance); 
    DEBUG.print(" | ");
    DEBUG.println(ballSeen); 
    // }else{
    // DEBUG.println("Not seeing ball");
    // }
}