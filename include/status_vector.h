#pragma once
#define dim 20
#include <Arduino.h>

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

input inputs[dim];
data datas[dim];