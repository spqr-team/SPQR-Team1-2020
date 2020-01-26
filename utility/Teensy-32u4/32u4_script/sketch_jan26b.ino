#define BTN0 A3
#define BTN1 A4
#define BTN2 A5
#define LED_Y 11
#define LED_R 17

void setup (){
  Serial1.begin(19200);
  
  pinMode(LED_Y,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(BTN0,INPUT);
  pinMode(BTN1,INPUT);
  pinMode(BTN2,INPUT);
}

byte b, oldB = 0;

void loop ()  {
  //We have three config. buttons, making a packet out of a single byte with a start header, so teensy can use it as it wants
  //The header is signed by the two most important bits put high, so 128+64 in OR with other bits shifted by the needed ammount
  //This approach only admits 5 configuration buttons, it should be enough
  b = 0b11000000;
  b |= digitalRead(BTN0);
  b |= digitalRead(BTN1) << 1;
  b |= digitalRead(BTN2) << 2;
  if(oldB != b) Serial1.write(b);  
  oldB = b;

  while(Serial1.available() > 0){
    int a = Serial1.read();
    if((a & 0b11000000) == 0b11000000){
      digitalWrite(LED_Y, !(a & 0b00000001));
      digitalWrite(LED_R, !(a & 0b00000010));
    }
  }
  int angle = (int) (atan2(3,2) * 180 / 3.14);
  angle = angle / 2 + angle % 2;
  int dist = 256;
  Serial1.write((char) 105); //Start packet
  Serial1.write((char) angle); //Start packet
  Serial1.write((char) dist); //Start packet
  Serial1.write((char) 115); //Start packet
}
