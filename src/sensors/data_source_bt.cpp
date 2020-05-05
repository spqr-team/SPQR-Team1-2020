#include "sensors/data_source_bt.h"

//if needed, substitute Serial1 with Serial3 to return to the old code setup

DataSourceBT :: DataSourceBT(HardwareSerial* ser_, int baud) : DataSource(ser_, baud){
    // connect();
}

void DataSourceBT :: connect(){
    Serial1.print("$");
    Serial1.print("$");
    Serial1.print("$");
    delay(100);
    Serial1.println("C");
}

void DataSourceBT :: reconnect(){
    if(!comrade){
    if(!b){
      Serial1.print("$");
      Serial1.print("$");
      Serial1.print("$");
    }else{
      Serial1.println("C");
    }

    b = !b;
  }else{
    Serial1.println("---");
  }
}

void DataSourceBT :: test(){
    if (DEBUG.available()) {
    DEBUG.println((char)DEBUG.read());
    }
    if (Serial1.available()) {
    Serial1.write((char)Serial1.read());
  }
}