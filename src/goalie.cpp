#include "goalie.h"

Goalie::Goalie(){

}

void Goalie::goalie(){
    digitalWrite(LED_G, HIGH);
    if(ball->ballSeen){
        if(ball->angle >= 0 && ball->angle < 45) drive->drive(ball->angle, 75, 0);
        else if(ball->angle >= 45 && ball->angle <= 60) drive->drive(ball->angle, 75, 0);
        else if(ball->angle > 60 && ball->angle < 90) drive->drive(ball->angle, 75, 0);
        else if(ball->angle >= 90 && ball->angle < 135) drive->drive(ball->angle, 75, 0); 
    } else {
        drive->prepareDrive(0, 0, 0);
        drive->drive(0, 0, 0);
    }
}

void Goalie::ballBack(){

}