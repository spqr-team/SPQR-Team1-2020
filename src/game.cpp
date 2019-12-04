#include "game.h"

Game::Game(){

}

void Game::goalie(){
    compass->readSensor();
    //drive->prepareDrive(0, 150, 0);
    digitalWrite(LED_G, HIGH);
    if(ball->ballSeen){
        if(ball->angle >= 0 && ball->angle <= 45) drive->drive(0, 75, 0);
        //else if(ball->angle <= 45) drive->drive(45, 75, 0);
        else if(ball->angle > 45 && ball->angle <= 90) drive->drive(90, 75, 0);
        //else if(ball->angle <= 135) drive->drive(135, 75, 0);
        else if(ball->angle > 90 && ball->angle <= 180) drive->drive(180, 75, 0);
    } else {
        drive->prepareDrive(0, 0, 0);
        drive->drive(0, 0, 0);
    }
}

void Game::keeper(){
    compass->readSensor();
    digitalWrite(LED_Y, HIGH);
    drive->prepareDrive(0, 0, 0);
    drive->drive(0, 0, 0);
}

void ballBack(){

}


