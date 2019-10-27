#include <Arduino.h>

class MOTOR {
    public:
        void initMot();
        void mot(byte mot, int vel);
    public:
        byte INA_MOT[5] = {0, 12, 25, 27, 21};
        byte INB_MOT[5] = {0, 11, 24, 26, 22};
        byte PWM_MOT[5] = {0, 2,   5,  6, 23};

        byte VAL_INA, VAL_INB;
        byte INA,INB, MPWM;
};
