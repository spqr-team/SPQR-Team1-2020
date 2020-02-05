#pragma once

#include <Arduino.h>

#ifdef STATUS_VECTOR_CPP
#define sv_extr 
#else
#define sv_extr extern
#endif

#define dim 20
#define CURRENT_DATA_READ (datas[(currentSVIndex-1) % dim])
#define CURRENT_DATA_WRITE (datas[(currentSVIndex) % dim])
#define CURRENT_INPUT_READ (inputs[(currentSVIndex-1) % dim])
#define CURRENT_INPUT_WRITE (inputs[(currentSVIndex) % dim])

typedef struct input{
    int IMUAngle, USfr, USsx, USdx, USrr, BT;
    byte ballByte, cameraByte, lineByte;
    bool SW_DX, SW_SX;
}input;

typedef struct data{
    int IMUAngle, ballAngle, ballDistance, cameraAngle, cameraDistance,
        speed, tilt, dir, USfr, USsx, USdx, USrr, lineOutDir, matePos, role;
    byte xb, yb, xy, yy, lineSeen, lineActive;
    bool mate, ATKgoal, DEFgoal;
}data;

sv_extr input inputs[dim];
sv_extr data datas[dim];
sv_extr int currentSVIndex;

void initStatusVector();
void updateStatusVector();