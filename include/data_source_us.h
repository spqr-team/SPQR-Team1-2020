#pragma once
#include "data_source.h"

#define US_WAIT_TIME 70

class DataSourceUS : public DataSource{

    public:
        DataSourceUS(TwoWire* i2c_, int addr);
        void postProcess() override;
        void test() override;
        void usMode();
        void usTrigger();
        void usReceive();
        void readSensor() override;

        int reading;
        long us_t0;                
        long us_t1;                
        bool us_flag;             
};