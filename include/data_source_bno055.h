#include "data_source.h"
#include <Adafruit_BNO055.h>
#include <Arduino.h>

class DataSourceBNO055 : public DataSource{

    public:
        DataSourceBNO055();
        void readSensor();
        void postProcess();
        
    public:
        Adafruit_BNO055 bno;

};