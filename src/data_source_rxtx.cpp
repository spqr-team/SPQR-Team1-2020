#include "data_source_rxtx.h"

void DataSourceRXTX::update(){
    while(ser.available() > 0) value = ser.read();

    postProcess();
}