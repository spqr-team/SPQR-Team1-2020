/*Use this script to reprogram the bluesmirf-rn42 using an arduino microcontroller.
Bluesmirf defaults the uart speed to 115200 after factory reset, so a SoftwareSerial may not be ideal for a long use, but it can be used to enter command mode and temp-change the uart speed to 9600 using the SU,9600 command
First of all it may be useful to reset the BT module to its factory settings, a useful video on how to do it can be found here: https://www.youtube.com/watch?v=8gZNF3bFpzI
Upload a Blink program to the arduino, when the pin is high give power to the module, an instant short-flashing on the status led followed by a couple of seconds of the led being off means that the module has been reset
Now you can connect with this script and setup the BT module:
Enter command mode sending $$ no line ending in serial
Give the following commands to setup the bluesmirf as intended for our use
Read the manual for further information about the commands used
SM,2           Trigger mode
SA,0           No authentication needed
SU,19200        Baud rate to 19200
SR, address    The address the module has to connect to
ST, number     Amount of time (in seconds) of inactivity after which the connection is terminated (1 is too low, 3 is used during the tests, 2 should to the thing)

When trying to connect one bluetooth module with another one, please make sure that the two are powered off with at least 300mS of difference: if they are trying to connect with each other at the same moment, the connection will fail
*/

#include <SoftwareSerial.h>

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

//SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
#define bluetooth Serial3

void setup() {
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  delay(1000);
  bluetooth.begin(19200);
}

void read() {
  while (bluetooth.available()) {
    // Send any characters the bluetooth pri$$$nts to the serial monitor
    Serial.print((char)bluetooth.read());
  }
}

void write() {
  while (Serial.available()) {
    // Send any characters the Serial monitor prints to the bluetooth
    char a = (char)Serial.read();
    bluetooth.print(a);
    Serial.print(a);
  }
  // and loop forever and ever!
}

void loop() {
  read();
  write();
}
