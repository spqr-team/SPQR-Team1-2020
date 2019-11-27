#include "data_source.h"

DataSource::DataSource(void){
    protocol = P_NULL;
}

DataSource::DataSource(TwoWire* i2c_, int addr){
    protocol = P_I2C;
    this->i2c = i2c_;    
    this->i2CAddr = addr;

    this->i2c->end();
    this->i2c->begin();
}

DataSource::DataSource(HardwareSerial* ser_, int baud){
    protocol = P_RXTX;
    this->ser = ser_;    
    ser->begin(baud);
}

DataSource::DataSource(int pin_, bool analog){
    this->pin = pin_;
    if(analog) protocol = P_APIN;
    else {
        protocol = P_DPIN;
        digitalWrite(pin, OUTPUT);
    }
}

int DataSource::getValue(){
    return value;
}

void DataSource::update(){
    readSensor();
    postProcess();
}

void DataSource::postProcess(){ }

void DataSource::readSensor(){
    if(protocol == 1) value = i2c->read();
    else if(protocol == 2) while(ser->available() > 0) value = ser->read();
    else if(protocol == 3) analogRead(pin);
    else if(protocol == 4) digitalRead(pin);
}

void DataSource::test(){
    this->update();
    DEBUG_PRINT.println(this->getValue());
}