#include "data_source.h"

class DataSourceRXTX : public DataSource{

    public:
        DataSourceRXTX(HardwareSerial);

        void update();

    public:
        HardwareSerial ser;
    
};