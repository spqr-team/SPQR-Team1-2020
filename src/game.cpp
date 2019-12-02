#include "game.h"

Game::Game(){

}

void Game::goalie(){
    compass->readSensor();
    digitalWrite(LED_G, HIGH);
    if(ball->ballSeen){
        if(ball->angle >= 0) {
            drive->prepareDrive(0, 50, 0);
            drive->drive(0, 50, 0);
    }
    } else drive->prepareDrive(0, 0, 0);
}

void Game::keeper(){
    compass->readSensor();
    digitalWrite(LED_Y, HIGH);
}


