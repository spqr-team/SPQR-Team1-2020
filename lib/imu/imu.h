#include <Arduino.h>

class IMU {
    public:
        void initIMU();
        int getEuler();
        int imu_current_euler;
};