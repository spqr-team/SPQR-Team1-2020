#include "sensors/data_source_ball_presence.h"
#include "behaviour_control/status_vector.h"
#include "vars.h"

DataSourceBallPresence::DataSourceBallPresence(int pin_, bool analog) : DataSource(pin_, analog){
    present = false;
    value = 0;
} 

void DataSourceBallPresence::postProcess(){
    present = value <= BALL_PRESENCE_TRESH;

    CURRENT_INPUT_WRITE.ballPresenceVal = value;
    CURRENT_DATA_WRITE.ballPresenceVal = value;
    CURRENT_DATA_WRITE.ballPresent = present;
}

bool DataSourceBallPresence::isInMouth(){
    return ball->isInFront() && present;
}

void DataSourceBallPresence::test(){
    DEBUG.print("Reading value: ");
    DEBUG.print(CURRENT_DATA_READ.ballPresenceVal);
    DEBUG.print(" -> ");
    DEBUG.print(CURRENT_DATA_READ.ballPresent);
    DEBUG.print(" | Ball in mouth: ");
    DEBUG.print(isInMouth());
}