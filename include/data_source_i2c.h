#include "data_source.h"
//i2c_t3

class DataSourceI2C : public DataSource{

    public:
        DataSourceI2C();
        DataSourceI2C(TwoWire);
        void update();

    public:
        TwoWire i2c;
    
};
