#pragma once
#include "data_source.h"
#include "vars.h"

class DataSourceBT : public DataSource{

    public:
        DataSourceBT(HardwareSerial* ser, int baud);
        void test() override;
        void connect();
        void reconnect();

        bool b, comrade;
};