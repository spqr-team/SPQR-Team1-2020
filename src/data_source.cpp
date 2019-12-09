#include "data_source.h"

DataSource::DataSource(void){
    protocol = P_NULL;
    
    value = 0;
}

DataSource::DataSource(TwoWire* i2c_, int addr){
    protocol = P_I2C;
    this->i2c = i2c_;    
    this->i2CAddr = addr;

    this->i2c->end();
    this->i2c->begin();

    value = 0;
}

DataSource::DataSource(HardwareSerial* ser_, int baud){
    protocol = P_RXTX;
    this->ser = ser_;    
    ser->begin(baud);
    
    value = 0;
}

DataSource::DataSource(int pin_, bool analog){
    this->pin = pin_;
    if(analog) protocol = P_APIN;
    else {
        protocol = P_DPIN;
        pinMode(pin, INPUT);
    }
    
    value = 0;
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
    if(protocol == P_I2C) value = i2c->read();
    else if(protocol == P_RXTX) while(ser->available() > 0) value = ser->read();
    else if(protocol == P_APIN) value = analogRead(pin);
    else if(protocol == P_DPIN) value = digitalRead(pin);
}

void DataSource::test(){
    this->update();
    DEBUG.println(this->getValue());
}