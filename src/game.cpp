#include "game.h"

Game::Game(){

}

void Game::goalie(){
    compass->readSensor();
    //drive->prepareDrive(0, 150, 0);
    digitalWrite(LED_G, HIGH);
    if(ball->ballSeen){
        if(ball->angle >= 0) drive->drive(0, 100, 0);
        else if(ball->angle <= 45) drive->drive(45, 100, 0);
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


