#include <Arduino.h>

/*
  * Author: EmaMaker on 26 Jan 2020
  * Experimenting with Teensy 3.5 <-> Atmega32u4 Bidirectional Serial communication
*/

#define LED1 32
#define LED2 31
#define LED3 30

void setup() {
  delay(2000);
  Serial5.begin(19200);
  Serial.begin(9600);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
  delay(2000);

  Serial.println("Teensy 3.5 working!");
}

int value;

int startp = 105;
int endp = 115;
bool start, end, data_received;
int led1 = 0, led2 = 0, led3 = 0, count = 0;
int angle, dist, angle_temp, dist_temp;
//As when transimitting from 32u4 to teensy, we use the same syntax to send a byte representing max 6 states to be displayed on LEDs on 32u4
byte b, oldB = 0;
void loop() {
  while(Serial5.available() > 0){
    value = (int)Serial5.read();
    if((value & 0b11000000) == 0b11000000){

    led1 = value & 0b0000001;
    led2 = value & 0b0000010;
    led3 = value & 0b0000100;
    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);
    digitalWrite(LED3, led3);
    }else{
      if(value==startp){
        start=true;
        count=0;
      }
      else if(value==endp){
        data_received=false;
        if(count==2 && start==true) {
          data_received=true;
          angle = angle_temp;
          dist = dist_temp;
          Serial.print(angle);
          Serial.print(" | ");
          Serial.println(dist);
        }
        end=true;
        start=false;
      }else{
        if(start==true){
          if (count==0) angle_temp=value;
          else if (count==1) dist_temp=value;
          count++;
        }
      }
    }
  }
  b = 0b11000000;
  b |= led1;
  b |= led2;
  b |= led3;
  if(oldB != b) Serial5.write(b);
  oldB = b;
}