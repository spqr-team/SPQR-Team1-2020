#pragma once

#include "behaviour_control/data_source.h"
#include "vars.h"

class DataSourceBT : public DataSource{

    public:
        DataSourceBT(HardwareSerial* ser, int baud);
        void test() override;
        void update() override;
        void connect();
        void receive();
        void send();

        bool can_bombard, bt_bombarded, comrade;
        unsigned long bt_timer, last_received, t;

        char received, tosend;
};