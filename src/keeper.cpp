#include "keeper.h"
#include "sensors.h"
#include "games.h"
#include <Arduino.h>

Keeper::Keeper() : Game() {
    defSpeed = 0;
    defDir = 0;
    angle = 0;
    angleX = 0;
    angleY = 0;
    t = 0;
    toh= 0;
    keeperAttackTimer = 0;
    keeper_tookTimer = false;
    keeper_backToGoalPost = false;
}

void Keeper::realPlay() {
    
    if(ball->distance > KEEPER_ATTACK_DISTANCE){
        // Ball is quite near
        goalie->play();
        if(!keeper_tookTimer){
            keeperAttackTimer = 0;
            keeper_tookTimer = true;
        }
        if(keeperAttackTimer > KEEPER_ALONE_ATTACK_TIME && keeper_tookTimer) keeper_backToGoalPost = true;

    }else{
        
        angle = (90 + ball->angle) * M_PI / 180;
        angleX = abs(cos(angle));

        if(ball->angle >= 0 && ball->angle <= 90 && camera->getValueDef(true) < 30) drive->prepareDrive(90, KEEPER_BASE_VEL*angleX*KEEPER_VEL_MULT);
        else if(ball->angle >= 270 && ball->angle <= 360  && camera->getValueDef(true) > -30) drive->prepareDrive(270, KEEPER_BASE_VEL*angleX*KEEPER_VEL_MULT);
        else if(ball->angle < 270 && ball->angle > 90){
            int ball_degrees2 = ball->angle > 180? ball->angle-360:ball->angle;
            int dir = ball_degrees2 > 0 ? ball->angle + KEEPER_BALL_BACK_ANGLE : ball->angle - KEEPER_BALL_BACK_ANGLE;
            dir = dir < 0? dir + 360: dir;
            
            drive->prepareDrive(dir, KEEPER_BASE_VEL);
        }
        //centerGoalPostCamera(false);    
    }
}