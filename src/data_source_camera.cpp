#include "data_source_camera.h"
#include "sensors.h"

DataSourceCamera::DataSourceCamera(HardwareSerial* ser_, int baud) : DataSource(ser_, baud){}

void DataSourceCamera :: readSensor(){
  while(ser->available() > 0){
    value = (int)ser->read();
    //Serial.println(value);
    if(value==startp){
      start=true;
      count=0;
    }
    else if(value==endp){
      end=true;
      start=false;
      data_received=false;
      if(count=4 && start==true) {
        data_received=true;
        true_xb = xb;
        true_yb = yb;
        true_xy = xy;
        true_yy = yy;
      }
    }else{
      if(start==true){
        if (count==0) xb=value;
        else if (count==1) yb=value;
        else if (count==2) xy=value;
        else if (count==3) yy=value;
        count++;
      }
    }   
  }
}


/* 
    for(int i=0;i<6;i++) reading[i]=(char)ser->read();
    if(reading[0]==startp) start=true;
      else if(reading[0]==endp && start==true) continue; 			
	  if(reading[1]==startp && (start==true || count==0)) continue; //ser->flush();	//ignoring data and continuing
      else if (reading[1] == unkn) unkn_counter++;//xb = oldxb;
	  else reading[1]=xb;
	  count++;  
	  if(reading[2]==startp && start==true) break;
	  else reading[2]=yb;
	  count++;
	  if(reading[3]==startp && start==true) break;
      else if (reading[3] == unkn) unkn_counter++;//xy = oldxy; //tried to do for now
	  else reading[3]=xy;
	  count++;
	  if(reading[4]==startp && start==true) break;
	  else reading[4]=yy;
	  count++;
	  if(reading[5]==endp && count==4){
	    end=true;
	    data_received=true;
	    start=false;
	  } 
*/
  /* portx = 999;
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
*/

void DataSourceCamera :: postProcess(){

  /*if (valY != -74)
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
  }*/
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
  update();
/*     DEBUG.print(pAtk);
    DEBUG.print(" | ");
    DEBUG.print(fixCamIMU(pAtk));
    DEBUG.print(" --- ");

    DEBUG.print(pDef);
    DEBUG.print(" | ");
    DEBUG.println(fixCamIMU(pDef));  */
    //update();
    DEBUG.print(xb);
    DEBUG.print("|");
    DEBUG.print(yb);
    DEBUG.print("|");
    DEBUG.print(xy);
    DEBUG.print("|");
    DEBUG.print(yy); 
    DEBUG.println("---------------");
    DEBUG.print(true_xb);
    DEBUG.print("|");
    DEBUG.print(true_yb);
    DEBUG.print("|");
    DEBUG.print(true_xy);
    DEBUG.print("|");
    DEBUG.print(true_yy); 
    DEBUG.println("---------------");
    delay(75);
}

int DataSourceCamera::fixCamIMU(int d){
    if(compass->getValue() > 0 && compass->getValue() < 180) imuOff = compass->getValue();
    else if (compass->getValue() <= 360 && compass->getValue() >= 180) imuOff = compass->getValue() - 360;
    imuOff = constrain(imuOff*0.8, -30, 30);

    return d + imuOff;
}