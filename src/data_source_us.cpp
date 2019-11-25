#include "data_source_us.h"
#include "vars.h"

DataSourceUS :: DataSourceUS(TwoWire* i2c_) : DataSource(i2c_) { 
    i2c->begin();   
}


void DataSourceUS :: postProcess(){
    usMode();
    us_fr = us_values[0]; // FRONT US
    us_dx = us_values[1]; // DX US
    us_px = us_values[2]; // BACK US
    us_sx = us_values[3]; // SX US
}

void DataSourceUS :: usMode(){
    if (us_flag == false) {
        usTrigger();
        us_flag = true;
        us_t0 = millis();
    } else {
        us_t1 = millis();
        if ((us_t1 - us_t0) > 70) {
        usReceive();
        us_flag = false;
    }
  }
}

void DataSourceUS :: usTrigger(){
    for (int i = 0; i < 4; i++){
        i2c->beginTransmission(112 + i);
        i2c->write(byte(0x00));
        i2c->write(byte(0x51));
        i2c->endTransmission();
    }
}

void DataSourceUS :: usReceive(){
    for (int i = 0; i < 4; i++){
        i2c->beginTransmission(112 + i);
        i2c->write(byte(0x00));
        i2c->write(byte(0x51));
        i2c->endTransmission();
        delay(70);
        i2c->requestFrom(112 + i, 2);
        if(2 <= i2c->available()){
            reading = i2c->read();
            reading = reading << 8;
            reading |= i2c->read();
            us_values[i] = reading;
        }
    }
}

void DataSourceUS :: test(){
    for (int i = 0; i < 4; i++){
        i2c->beginTransmission(112 + i);
        i2c->write(byte(0x00));
        i2c->write(byte(0x51));
        i2c->endTransmission();
        delay(70);
        i2c->requestFrom(112 + i, 2);
        if(2 <= i2c->available()){
            reading = i2c->read();
            reading = reading << 8;
            reading |= i2c->read();
            us_values[i] = reading;
        }
    }
    us_fr = us_values[0];
    us_dx = us_values[1];
    us_px = us_values[2];
    us_sx = us_values[3];

    //printing the result
    DEBUG_PRINT.println("---------------------");
    for (int i = 0; i < 4; i++) {
    DEBUG_PRINT.println(us_values[i]);
    delay(250);
    }
    DEBUG_PRINT.println("---------------------");
}