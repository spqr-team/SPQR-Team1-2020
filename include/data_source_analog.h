#include "data_source.h"

class DataSourceAnalog : public DataSource{

    public:
        DataSourceAnalog(int);

    public:
        int pin;
    
};