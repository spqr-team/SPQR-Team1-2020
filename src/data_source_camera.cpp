#include "data_source_camera.h"
#include "sensors.h"

DataSourceCamera::DataSourceCamera(HardwareSerial* ser_, int baud) : DataSource(ser_, baud){}

void DataSourceCamera :: readSensor(){
  portx = 999;
  while(ser->available() > 0) {
    value = ser->read();
    // if the incoming character is a 'Y', set the start packet flag
    if (value == 'Y') {
      startpY = 1;
    }
    // if the incoming character is a 'Y', set the start packet flag
    if (value == 'B') {
      startpB = 1;
    }
    // if the incoming character is a '.', set the end packet flag
    if (value == 'y') {
      endpY = 1;
    }
    // if the incoming character is a '.', set the end packet flag
    if (value == 'b') {
      endpB = 1;
    }

    if ((startpY == 1) && (endpY == 0)) {
      if (isDigit(value)) {
        // convert the incoming byte to a char and add it to the string:
        valStringY += value;
      }else if(value == '-'){
        negateY = true;
      }
    }

    if ((startpB == 1) && (endpB == 0)) {
      if (isDigit(value)) {
        // convert the incoming byte to a char and add it to the string:
        valStringB += value;
      }else if(value == '-'){
        negateB = true;
      }
    }

    if ((startpY == 1) && (endpY == 1)) {
      valY = valStringY.toInt(); // valid data
      if(negateY) valY *= -1;
      valStringY = "";
      startpY = 0;
      endpY = 0;
      negateY = false;
      datavalid ++;
    }
    if ((startpB == 1) && (endpB == 1)) {
      valB = valStringB.toInt(); // valid data
      if(negateB) valB *= -1;
      valStringB = "";
      startpB = 0;
      endpB = 0;
      negateB = false;
      datavalid ++;
    }
  }
}

void DataSourceCamera :: postProcess(){

  if (valY != -74)
    oldGoalY = valY;
  if (valB != -74)
    oldGoalB = valB;

  if (valY == -74)
    valY = oldGoalY;
  if (valB == -74)
    valB = oldGoalB;
  
  // entro qui solo se ho ricevuto i pacchetti completi sia del blu che del giallo
  if (datavalid > 1 ) {
    if(goalOrientation == 1){
      //yellow goalpost
      pAtk = valY;
      pDef = valB * -1;
    }else{
      //blue goalpost
      pAtk = valB;
      pDef = valY * -1;
    }

    datavalid = 0;
    cameraReady = 1;  //attivo flag di ricezione pacchetto
  }
}

int DataSourceCamera::getValueAtk(bool fixed){
  //attacco gialla
  if(digitalRead(SWITCH_DX) == HIGH){
    if(fixed) return fixCamIMU(valY);
    return valY;
  }
  //attacco blu
  if(digitalRead(SWITCH_DX) == LOW){
    if(fixed) return fixCamIMU(valB);
    return valB;
  }
}

int DataSourceCamera::getValueDef(bool fixed){
  //difendo gialla
  if(digitalRead(SWITCH_DX) == HIGH){
    if(fixed) return fixCamIMU(valY);
    return valY;
  }
  //difendo blu
  if(digitalRead(SWITCH_DX) == LOW){
    if(fixed) return fixCamIMU(valB);
    return valB;
  }
}

void DataSourceCamera::test(){
    goalOrientation = digitalRead(SWITCH_SX);     //se HIGH attacco gialla, difendo blu
    

    DEBUG.print(pAtk);
    DEBUG.print(" | ");
    DEBUG.print(fixCamIMU(pAtk));
    DEBUG.print(" --- ");

    DEBUG.print(pDef);
    DEBUG.print(" | ");
    DEBUG.println(fixCamIMU(pDef));
    delay(100);
}

int DataSourceCamera::fixCamIMU(int d){
    if(compass->getValue() > 0 && compass->getValue() < 180) imuOff = compass->getValue();
    else if (compass->getValue() <= 360 && compass->getValue() >= 180) imuOff = compass->getValue() - 360;
    imuOff = constrain(imuOff*0.8, -30, 30);

    return d + imuOff;
}