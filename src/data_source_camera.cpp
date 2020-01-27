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

        //Remap from [0,100] to [-50, +49] to correctly compute angles and distances and calculate them
        yAngle = atan2(50-true_yy, 50-true_xy) * 180 / 3.14;
        bAngle = atan2(50-true_yb, 50-true_xb) * 180 / 3.14;
        //Subtract 90 to bring the angles back to euler angles (0 in front)
        yAngle = 90 - yAngle;
        bAngle = 90 - bAngle;
        //Now cast angles to [0, 359] domain angle flip them
        yAngle = (yAngle + 360) % 360;
        bAngle = (bAngle + 360) % 360;

        yAngleFix = yAngle - compass->getValue()*0.9 ;
        bAngleFix = bAngle - compass->getValue()*0.9  ;

        yDist = sqrt( (50-true_yy)*(50-true_yy) + (50-true_xy)*(50-true_xy) );
        bDist = sqrt( (50-true_yb)*(50-true_yb) + (50-true_xb)*(50-true_xb) );
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


int DataSourceCamera::getValueAtk(bool b){
  return 0;
}
int DataSourceCamera::getValueDef(bool b){
  return 0;
}

void DataSourceCamera::test(){
  goalOrientation = digitalRead(SWITCH_SX);     //se HIGH attacco gialla, difendo blu
  update();
    DEBUG.print(bAngle);
    DEBUG.print(" | ");
    DEBUG.print(bAngleFix);
    DEBUG.print(" | ");
    DEBUG.println(bDist);
    DEBUG.println(" --- ");

    DEBUG.print(yAngle);
    DEBUG.print(" | ");
    DEBUG.print(yAngleFix); 
    DEBUG.print(" | ");
    DEBUG.println(yDist);
    DEBUG.println("---------------");
    DEBUG.print(true_xb);
    DEBUG.print("|");
    DEBUG.print(true_yb);
    DEBUG.print("|");
    DEBUG.print(true_xy);
    DEBUG.print("|");
    DEBUG.println(true_yy); 
    DEBUG.println("---------------");
    delay(150);
}
