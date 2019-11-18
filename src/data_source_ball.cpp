#include "data_source_ball.h"
#include "vars.h"

DataSourceBall::DataSourceBall(usb_serial_class ser_, int baud) : DataSource(ser_, baud) {
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
    DEBUG_PRINT.print(angle); 
    DEBUG_PRINT.print(" | ");
    DEBUG_PRINT.println(distance); 
    }else{
    DEBUG_PRINT.println("Not seeing ball");
    }
}