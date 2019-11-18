#include "data_source_camera.h"
#include "sensors.h"

DataSourceCamera::DataSourceCamera(HardwareSerial* ser_, int baud) : DataSource(ser_, baud){}

void DataSourceCamera :: readSensor(){
  portx = 999;
  while(ser->available() > 0) value = ser->read();
}

void DataSourceCamera :: postProcess(){
    // if the incoming character is a 'Y', set the start packet flag
    if (inChar == 'Y') {
      startpY = 1;
    }
    // if the incoming character is a 'Y', set the start packet flag
    if (inChar == 'B') {
      startpB = 1;
    }
    // if the incoming character is a '.', set the end packet flag
    if (inChar == 'y') {
      endpY = 1;
    }
    // if the incoming character is a '.', set the end packet flag
    if (inChar == 'b') {
      endpB = 1;
    }

    if ((startpY == 1) && (endpY == 0)) {
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        valStringY += inChar;
      }else if(inChar == '-'){
        negateY = true;
      }
    }

    if ((startpB == 1) && (endpB == 0)) {
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        valStringB += inChar;
      }else if(inChar == '-'){
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

  } // end of while

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
    if(goal_orientation == 1){
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

void DataSourceCamera :: test(){
    goalOrientation = digitalRead(SWITCH_SX);     //se HIGH attacco gialla, difendo blu
    

    DEBUG_PRINT.print(pAtk);
    DEBUG_PRINT.print(" | ");
    DEBUG_PRINT.print(fixCamIMU(pAtk));
    DEBUG_PRINT.print(" --- ");

    DEBUG_PRINT.print(pDef);
    DEBUG_PRINT.print(" | ");
    DEBUG_PRINT.println(fixCamIMU(pDef));
    delay(100);
}

void DataSourceCamera :: fixCamIMU(int d){
    if(compass->getValue() > 0 && compass->getValue() < 180) imuOff = compass->getValue();
    else if (compass->getValue() <= 360 && compass->getValue() >= 180) imuOff = compass->getValue() - 360;
    imuOff = constrain(imuOff*0.8, -30, 30);

    return d + imuOff;
}