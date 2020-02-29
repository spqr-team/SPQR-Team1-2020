#include "sensors/data_source_bt.h"

DataSourceBT :: DataSourceBT(HardwareSerial* ser_, int baud) : DataSource(ser_, baud){
    // connect();
}

void DataSourceBT :: connect(){
    Serial3.print("$");
    Serial3.print("$");
    Serial3.print("$");
    delay(100);
    Serial3.println("C");
}

void DataSourceBT :: reconnect(){
    if(!comrade){
    if(!b){
      Serial3.print("$");
      Serial3.print("$");
      Serial3.print("$");
    }else{
      Serial3.println("C");
    }

    b = !b;
  }else{
    Serial3.println("---");
  }
}

void DataSourceBT :: test(){
    if (DEBUG.available()) {
    DEBUG.println((char)DEBUG.read());
    }
    if (Serial3.available()) {
    Serial3.write((char)Serial3.read());
  }
}