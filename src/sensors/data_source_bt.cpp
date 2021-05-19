#include "sensors/data_source_bt.h"

/*Currently using a master-slave setup
One bt has been setup using
SM,3 - Master mode
SA, 0 - Disable authentication
SR, xxxx - Address of the other bt
SU,96 - baud rate 9600
SN, name - Name for clarity

The other one
SM,0 - Master mode
SA, 0 - Disable authentication
SU,96 - baud rate 9600
SN, name - Name for clarity
ST, 5 - Configuration timeout

For now it seems that a slave can easily recovery from a master restart, but not the opposite. We will make sure that doesn't happen
*/


DataSourceBT :: DataSourceBT(HardwareSerial* ser_, int baud) : DataSource(ser_, baud){
    bt_timer = millis();
    can_bombard = false;
    bt_bombarded = false;

    comrade = false;

    last_received = 0;
    t = 0;

    tosend = 'A';
    received = '0';

    connect();
}

void DataSourceBT :: connect(){
  //Give the bt time to be brought up (about 5-6 secs.)
  //When turned on the bt onboard led will blink. After 5-6 secs it will start blinking at a lower freq. We need to wait for that to happen
  // if(millis() >= bt_timer + 5000 && !bt_bombarded){
  //   can_bombard = true;
  // }

  // //For a sec, bombard the other bt of packets. Since we are in sm2 this will make them connect. Note that the two of them cannot accept connections while they're trying to connect
  // if(can_bombard && millis() >= bt_timer + 5000 && millis() <= bt_timer + 6000){
  //   DEBUG.println("Bombarding");
  //   Serial1.print(tosend);
  //   bt_bombarded = true;
  // }else{
  //   can_bombard = false;
  // }

}

void DataSourceBT :: receive(){
  while(Serial1.available()) {
    last_received = millis();
    received = (char) Serial1.read();
    comrade = true;
  }
  if(millis() - last_received > 2000) 
  comrade = false;
}

void DataSourceBT::send(){
  if(millis() - t >= 250){
    Serial1.print(tosend);
  }
}

void DataSourceBT::update(){
  // if(!bt_bombarded && can_bombard) connect();
  receive();
  send();
  // if(comrade)Serial2.write(0b00000100);
}

void DataSourceBT :: test(){
    if (DEBUG.available()) {
    DEBUG.println((char)DEBUG.read());
    }
    if (Serial1.available()) {
    Serial1.write((char)Serial1.read());
  }
}