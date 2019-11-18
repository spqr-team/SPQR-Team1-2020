#include "data_source.h"

class DataSourceCamera : public DataSource{

    public:
        DataSourceCamera(HardwareSerial* ser, int baud);
        void postProcess() override;
        void test() override;
        void fixCamIMU(int);
        
        int goalOrientation, pAtk, pDef, imuOff, portx, valX, valY, valB, oldGoalX, oldGoalY, oldGoalB;
        int cameraready;
        char value;
        int startpY = 0;
        int startpB = 0;
        int endpY = 0; 
        int endpB = 0;
        int datavalid = 0;
        String valStringY = ""; 
        String valStringB = "";
        bool negateB, negateY;
};