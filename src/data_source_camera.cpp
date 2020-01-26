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
      data_received=false;
      if(count=4 && start==true) {
        data_received=true;
        true_xb = xb;
        true_yb = yb;
        true_xy = xy;
        true_yy = yy;

        //Remap to [-50, +49] to correctly compute angles and distances
        true_xb -= 50;
        true_yb -= 50;
        true_xy -= 50;
        true_yy -= 50;

        //Now calculate angles and distance
        yAngle = atan2(true_yy, true_xy) * 180 / 3.14;
        bAngle = atan2(true_yb, true_xb) * 180 / 3.14;
        yAngleFix = yAngle - compass->getValue() ;
        bAngleFix = bAngle - compass->getValue() ;

        yDist = sqrt( true_yy*true_yy  + true_xy*true_xy );
        bDist = sqrt( true_yb*true_yb  + true_xb*true_xb );
      }
      end=true;
      start=false;
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


void DataSourceCamera :: postProcess(){
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
    DEBUG.print(yAngle);
    DEBUG.print(" | ");
    DEBUG.print(yAngleFix);
    DEBUG.println(" --- ");

    DEBUG.print(bAngle);
    DEBUG.print(" | ");
    DEBUG.println(bAngleFix); 
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