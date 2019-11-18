#include "data_source.h"

class DataSourceBall : public DataSource{

    public:
        DataSourceBall(usb_serial_class ser, int baud);
        void postProcess() override;
        void test() override;
        int angle,distance;
        bool ballSeen;
};