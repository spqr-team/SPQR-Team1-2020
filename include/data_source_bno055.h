#include "data_source_i2c.h"
#include <Adafruit_BNO055.h>
#include <Arduino.h>

class DataSourceBN0O55 : public DataSourceI2C{

    public:
        DataSourceBN0O55();
        void update();

    public:
        int value;
        Adafruit_BNO055 bno;
    
};