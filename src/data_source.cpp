#include "data_source.h"

DataSource::DataSource(void){
    protocol = 0;
}

DataSource::DataSource(TwoWire i2c_){
    
    i2c = &(i2c_);
    protocol = 1;
    
    i2c->begin();

}

DataSource::DataSource(HardwareSerial ser_, int baud){
    ser = &(ser_);
    protocol = 2;
    
    ser->begin(baud);
}

DataSource::DataSource(int pin_, bool analog){
    pin = pin_;
    if(analog) protocol = 3;
    else protocol = 4;
}

int DataSource::getValue(){
    return value;
}

void DataSource::update(){
    readSensor();
    postProcess();
}

void DataSource::postProcess(){

}

void DataSource::readSensor(){
    if(protocol == 1) value = i2c->read();
    else if(protocol == 2) while(ser->available() > 0) value = ser->read();
    else if(protocol == 3) analogRead(pin);
    else if(protocol == 4) digitalRead(pin);
}

void DataSource::test(){
    update();
    DEBUG_PRINT.println(getValue());
}