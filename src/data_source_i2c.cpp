#include "data_source_i2c.h"

void DataSourceI2C::update(){
    value = i2c.read();
}