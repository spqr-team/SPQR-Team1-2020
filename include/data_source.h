#pragma once

#include "Wire.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include "vars.h"

class DataSource {

    public:
        DataSource();
        DataSource(HardwareSerial*, int);
        DataSource(TwoWire* , int);
        DataSource(int, bool);

    public: 
        virtual void update();
        virtual void test();
        virtual void readSensor();
        virtual void postProcess();
        virtual int getValue();


    public:
        enum Protocols {
            P_NULL,
            P_I2C,
            P_RXTX,
            P_APIN,
            P_DPIN            
        };
        
        HardwareSerial* ser;
        TwoWire* i2c;
        int i2CAddr;

        Protocols protocol;
        int pin;
        int value;
        


};