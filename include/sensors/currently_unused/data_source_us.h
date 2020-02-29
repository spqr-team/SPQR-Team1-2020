#pragma once
#include "behaviour_control/data_source.h"

#define US_WAIT_TIME 70

class DataSourceUS : public DataSource{

    public:
        DataSourceUS(TwoWire* i2c_, int addr);
        void test() override;
        void readSensor() override;
        
        void usMode();
        void usTrigger();
        void usReceive();

        int reading;
        long us_t0;                
        long us_t1;                
        bool us_flag;       
};