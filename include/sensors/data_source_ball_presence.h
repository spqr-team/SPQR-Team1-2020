#pragma once

#define BALL_PRESENCE_TRESH 600

#include <Arduino.h>
#include "behaviour_control/data_source.h"

class DataSourceBallPresence : public DataSource{

    public:
        DataSourceBallPresence(int, bool);
        void postProcess() override;
        void test() override;
        bool isInMouth();

    public:
        bool present;
};