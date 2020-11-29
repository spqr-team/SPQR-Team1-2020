/*For some reason in our board, which I've been explained but I'm not capable of explaining it again, including LED1 and LED4 being part of usb serial,
we can't use plain pinMode and digitalWrite on those pins (at least the output ones, for what I've tried so far), so we gotta use registers and modify them manually
While this is a bit of a PITA, runs faster on the the uC
Also using Arduino Micro bootloader, seems to work fine
If Arduino Micro bl doesn't appear to work right, try the Sparkfun ProMicro ones

-EmaMaker 29/11/2020 22:47 CET
*/


// the setup function runs once when you press reset or power the board
void setup() {
  //LED3(PB7) and LED4 (PB0)
  DDRB=0b10000001;
  //LED2 (PF0)
  DDRF=0b00000001;
  //LED1 (PD5)
  DDRD=0b00100000;
}

// the loop function runs over and over again forever
void loop() {
  //Set the pins HIGH, using OR the pins we don't care about are not touched
  PORTB = PORTB | 0b10000001;
  PORTF = PORTF | 0b00000001;
  PORTD = PORTD | 0b00100000;
  
  delay(1000);

  //Set the pins LOW, using AND the pins we don't care about are not touched
  PORTB = PORTB & 0b01111110;
  PORTF = PORTF & 0b01111110;
  PORTD = PORTD & 0b11011111;
  
  delay(1000);
}
