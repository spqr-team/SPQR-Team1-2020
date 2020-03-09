/*Author: EmaMaker (emamaker.altervista.org) on 8/3/2020
  Write and read data from two bluesmirf rn-42 at the same time*/
#include <SoftwareSerial.h>

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

//SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
#define bluetooth1 Serial3
#define bluetooth2 Serial2

HardwareSerial* current= nullptr;

char a = ' ';

void setup() {
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth1.begin(19200);
  bluetooth2.begin(19200);
}

void read(HardwareSerial* bluetooth) {
  while (bluetooth->available()) {
    if(bluetooth == &bluetooth1){
      Serial.print("Bluetooth1 Read: ");
    }else if(bluetooth == &bluetooth2){
      Serial.print("Bluetooth2 Read: ");
    }
    // Send any characters the bluetooth prints to the serial monitor
    Serial.println((char)bluetooth->read());
    delay(50);
  }
}

void write(HardwareSerial* bluetooth) {
  if(a != ' ') {
    if(bluetooth == &bluetooth1){
      Serial.print("Bluetooth1 Write: ");
    }else if(bluetooth == &bluetooth2){
      Serial.print("Bluetooth2 Write: ");
    }
    // Send any characters the Serial monitor prints to the bluetooth
    Serial.println(a);
    bluetooth->print(a);
    a = ' ';
  }
}

bool b = false;
void loop() {
  b = !b;
  
  while(Serial.available() > 0){
    a = (char)Serial.read();
    if(a == '-') current = &bluetooth1;
    else if(a == '_') current = &bluetooth2;
    if(a == '-' || a == '_') a = ' ';
  }

  if(current != nullptr) write(current);

  read(&bluetooth1);
  read(&bluetooth2);
}
