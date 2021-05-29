#include "behaviour_control/status_vector.h"
#include "sensors/data_source_ball.h"
#include "vars.h"

DataSourceBall :: DataSourceBall(HardwareSerial* ser_, int baud) : DataSource(ser_, baud) {
  ballSeen = false;
  distance = 0;
  angle = 0;
}

// bool startAng = false, endAng= false, startDist = false, endDist = false;
// String valAngle;
// String valDist;

// char valueChar;

void DataSourceBall::readSensor(){
  while(ser->available()) ballString = ser->readStringUntil('B');
}

void DataSourceBall :: postProcess(){
  CURRENT_INPUT_WRITE.ballString = ballString;
  
  bool valid_data = false;
  String ballAngle_str, ballDist_str;

  if(ballString.length() == 9 && ballString.startsWith('b') && ballString.endsWith('I')){                         //String has a fixed length of 9 (3*2 for data, 3 for packet recognition)
    
    //Try to validate data data, extract data from String
    valid_data = true;

    //String is in the form of bXXX-YYYB, with XXX being ball angle and YYY being ball distance
    ballAngle_str = ballString.substring(ballString.lastIndexOf('b')+1, ballString.lastIndexOf('-'));
    ballDist_str = ballString.substring(ballString.lastIndexOf('-')+1, ballString.lastIndexOf('I'));

    
    // Check if strings only contain digits
    for(signed int i = 0; i < ballAngle_str.length(); i++)
      if (!isDigit(ballAngle_str.charAt(i))) valid_data = false;
    for(signed int i = 0; i < ballDist_str.length(); i++)
      if (!isDigit(ballDist_str.charAt(i))) valid_data = false;

    if(valid_data){
      angle = ballAngle_str.toInt();
      distance = ballDist_str.toInt();

      // Invalid data if out of parameters
      if(angle < 0 || angle >= 360 || distance < 0 || distance > 250) valid_data = false;
    }
  }

  if(valid_data){
    ballSeen = distance == 255 ? 0 : 1;

    int imuAngle = CURRENT_DATA_READ.IMUAngle > 180 ? CURRENT_DATA_READ.IMUAngle - 360 : CURRENT_DATA_READ.IMUAngle;
    angleFix = (angle+imuAngle+360)%360;
    
    CURRENT_DATA_WRITE.ballAngle = angle;
    CURRENT_DATA_WRITE.ballAngleFix = angleFix;
    CURRENT_DATA_WRITE.ballDistance = distance;
    CURRENT_DATA_WRITE.ballSeen = ballSeen;
  }else{
    // Invalid data, recover from last loop and clear the buffer to prevent corruption of following data
    CURRENT_DATA_WRITE.ballAngle = CURRENT_DATA_READ.ballAngle;
    CURRENT_DATA_WRITE.ballAngleFix =  CURRENT_DATA_READ.ballAngleFix;
    CURRENT_DATA_WRITE.ballDistance =  CURRENT_DATA_READ.ballDistance;
    CURRENT_DATA_WRITE.ballSeen =  CURRENT_DATA_READ.ballSeen;
  }
  
}

void DataSourceBall :: test(){
    this->update();
    DEBUG.println("Receiving of string: " + ballString + " resulted in: ");
    DEBUG.print(angle); 
    DEBUG.print(" | ");
    DEBUG.print(angleFix); 
    DEBUG.print(" | ");
    DEBUG.print(distance); 
    DEBUG.print(" | ");
    DEBUG.println(ballSeen); 
}

bool DataSourceBall::isInFront(){
  return CURRENT_DATA_READ.ballSeen && (CURRENT_DATA_READ.ballAngle > MOUTH_MIN_ANGLE || CURRENT_DATA_READ.ballAngle < MOUTH_MAX_ANGLE );
}

bool DataSourceBall::isInMouth(){
  return isInFront() && CURRENT_DATA_READ.ballDistance<=MOUTH_DISTANCE;
}

bool DataSourceBall::isInMouthMaxDistance(){
  return isInFront() && CURRENT_DATA_READ.ballDistance <= MOUTH_MAX_DISTANCE;
}