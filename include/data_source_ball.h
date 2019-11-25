#pragma once
#include "data_source.h"

class DataSourceBall : public DataSource{

    public:
        DataSourceBall(HardwareSerial* ser, int baud);
        void postProcess() override;
        void test() override;
        
        int angle,distance;
        bool ballSeen;
};