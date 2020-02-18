#include "data_source_us.h"
#include "vars.h"
#include "status_vector.h"


DataSourceUS::DataSourceUS(TwoWire* i2c_, int addr) : DataSource(i2c_, addr){
  us_flag = false;
  value = 0;
}

void DataSourceUS::test(){
  
  // test from srf02_example
    // step 1: instruct sensor to read echoes
    // transmit to device #112 (0x70)
    Wire1.beginTransmission(i2CAddr);
    // sets register pointer to the command register (0x00)
    Wire1.write(byte(0x00));
    // command sensor to measure in "centimeters" (0x51). 0x50 inches and 0x52
    // microseconds
    Wire1.write(byte(0x51));
    // stop transmitting
    Wire1.endTransmission();
    // step 2: wait for readings to happen
    // datasheet suggests at least 65 milliseconds
    delay(70);

    // step 3: instruct sensor to return a particular echo reading
    // transmit to device #112
    Wire1.beginTransmission(i2CAddr);
    // sets register pointer to echo #1 register (0x02)
    Wire1.write(byte(0x02));
    Wire1.endTransmission();

    // step 4: request reading from sensor
    // request 2 bytes from slave device #112
    Wire1.requestFrom(i2CAddr, 2);

    // step 5: receive reading from sensor
    if (2 <= Wire1.available()) {
      // if two bytes were received
      // receive high byte (overwrites  previous reading)
      reading = Wire1.read();
      // shift high byte to be high 8 bits
      reading = reading << 8;
      // receive low byte as lower 8 bit
      reading |= Wire1.read();
      value = reading;
    }

  DEBUG.println(value);
}

void DataSourceUS::readSensor(){
  if (us_flag == false) {
    usTrigger();
    us_flag = true;
    us_t0 = millis();
  } else {
    us_t1 = millis();
    if ((us_t1 - us_t0) > US_WAIT_TIME) {
      usReceive();
      us_flag = false;
    }
  }
}

void DataSourceUS::usTrigger() {
    // step 1: instruct sensor to read echoes
    // transmit to device #112 (0x70)
    i2c->beginTransmission(i2CAddr);
    // sets register pointer to the command register (0x00)
    i2c->write(byte(0x00));
    // command sensor to measure in "centimeters" (0x51). 0x50 inches and 0x52
    // microseconds
    i2c->write(byte(0x51));
    i2c->endTransmission();
}

void DataSourceUS::usReceive() {
  // transmit to device #112s
  i2c->beginTransmission(i2CAddr);
  // sets register pointer to echo 1 register(0x02)
  i2c->write(byte(0x02));
  i2c->endTransmission();

  // step 4: request reading from sensor
  // request 2 bytes from slave device #112
  i2c->requestFrom(i2CAddr, 2);

  // step 5: receive reading from sensor
  // receive high byte (overwrites  previous reading)
  reading = i2c->read();
  // shift high byte to be high 8 bits
  reading = reading << 8;
  // receive low byte as lower 8 bit
  reading |= i2c->read();
  value = reading;

  switch(i2CAddr){
    case 112:
    CURRENT_INPUT_WRITE.USfr = value;
    CURRENT_DATA_WRITE.USfr = value;
    break;
    case 113:
    CURRENT_INPUT_WRITE.USdx = value;
    CURRENT_DATA_WRITE.USdx = value;
    break;
    case 114:
    CURRENT_INPUT_WRITE.USrr = value;
    CURRENT_DATA_WRITE.USrr = value;
    break;
    case 115:
    CURRENT_INPUT_WRITE.USsx = value;
    CURRENT_DATA_WRITE.USsx = value;
    break;
  }
}