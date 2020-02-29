#pragma once

#include "behaviour_control/data_source.h"
#include "vars.h"
#include <Arduino.h>
#include <vector>

using namespace std;
class DataSourceCtrl {

    public:
        DataSourceCtrl();
        DataSourceCtrl(vector<DataSource*>);

    public:
        virtual void update();
        virtual void test();
        virtual void postProcess();
        virtual void read();
        int getValue(int i);

        vector<DataSource*> ds;

};