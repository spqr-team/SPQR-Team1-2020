#pragma once

#include "Wire.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include "vars.h"

class DataSource {

    public:
        DataSource();
        DataSource(HardwareSerial, int);
        DataSource(TwoWire);
        DataSource(int, bool);

    public: 
        void update();
        void test();
        void readSensor();
        void postProcess();
        int getValue();


    public:
        HardwareSerial* ser;
        TwoWire* i2c;

        int pin;
        int protocol;
        int value;
        

};