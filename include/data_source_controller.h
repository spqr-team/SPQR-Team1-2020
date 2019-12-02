#include "data_source.h"
#include "vars.h"
#include <Arduino.h>
#include <vector>

using namespace std;
class DataSourceController {

    public:
        DataSourceController();
        DataSourceController(vector<DataSource*>);

    public:
        void update();
        void test();
        void postProcess();
        void readSensor();
        void getValue();

        vector<DataSource*> ds;

};