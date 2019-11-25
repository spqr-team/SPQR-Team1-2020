#pragma once
#include "data_source.h"

class DataSourceUS : public DataSource{

    public:
        DataSourceUS(TwoWire* i2c_);
        void postProcess() override;
        void test() override;
        void usMode();
        void usTrigger();
        void usReceive();
        //void readSensor() override;

        int reading;
        long us_t0;                
        long us_t1;                
        bool us_flag;              
        int us_values[4];             
        int us_sx, us_dx, us_px, us_fr;      
};