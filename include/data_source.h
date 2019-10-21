#include "Wire.h"
#include "Arduino.h"
#include "HardwareSerial.h"

class DataSource {
    
    public:
        float value;
        
    public: 
        void update();
        void test();
        void postProcess();
        int getValue();

};