#pragma once

#include <Adafruit_BNO055.h>
#include <Arduino.h>

#include "behaviour_control/data_source.h"

#define DATA_CLOCK 10

class DataSourceBNO055 : public DataSource{

    public:
        DataSourceBNO055();
        void readSensor() override;
        
    public:
        Adafruit_BNO055 bno;
        unsigned long lastTime;

};