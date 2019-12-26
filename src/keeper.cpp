#include "keeper.h"
#include "sensors.h"
#include "games.h"
#include <Arduino.h>

Keeper::Keeper() : Game() {
    init();
}

Keeper::Keeper(LineSystem* ls_, PositionSystem* ps_) : Game(ls_, ps_){}

void Keeper::init(){
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
        
        angle = (KEEPER_ANGLE_DX + ball->angle) * M_PI / 180;
        angleX = abs(cos(angle));

        if(ball->angle >= 0 && ball->angle <= KEEPER_ANGLE_DX && camera->getValueDef(true) < 30) drive->prepareDrive(KEEPER_ANGLE_DX, KEEPER_BASE_VEL*angleX*KEEPER_VEL_MULT);
        else if(ball->angle >= KEEPER_ANGLE_SX && ball->angle <= 360  && camera->getValueDef(true) > -30) drive->prepareDrive(KEEPER_ANGLE_SX, KEEPER_BASE_VEL*angleX*KEEPER_VEL_MULT);
        else if(ball->angle < KEEPER_ANGLE_SX && ball->angle > KEEPER_ANGLE_DX){
            int ball_degrees2 = ball->angle > 180? ball->angle-360:ball->angle;
            int dir = ball_degrees2 > 0 ? ball->angle + KEEPER_BALL_BACK_ANGLE : ball->angle - KEEPER_BALL_BACK_ANGLE;
            dir = dir < 0? dir + 360: dir;
            
            drive->prepareDrive(dir, KEEPER_BASE_VEL);
        }
    }
}

void Keeper::centerGoalPostCamera(bool checkBack){
    if (camera->getValueDef(true) > CENTERGOALPOST_CAM_MAX) {
        drive->prepareDrive(KEEPER_ANGLE_SX, CENTERGOALPOST_VEL1);
    } else if (camera->getValueDef(true) < CENTERGOALPOST_CAM_MIN) {
        drive->prepareDrive(KEEPER_ANGLE_DX, CENTERGOALPOST_VEL1);
    }else if(camera->getValueDef(true) > CENTERGOALPOST_CAM_MIN && camera->getValueDef(true) < CENTERGOALPOST_CAM_MAX){
        if(!ball->ballSeen) drive->prepareDrive(0, 0, 0);
        if(checkBack){
            if(usCtrl->getValue(2) > CENTERGOALPOST_US_MAX){
                drive->prepareDrive(180, CENTERGOALPOST_VEL2);
            } else{
                if(usCtrl->getValue(2) < CENTERGOALPOST_US_CRITIC) drive->prepareDrive(0, CENTERGOALPOST_VEL3);

                keeper_backToGoalPost = false;
                keeper_tookTimer = false;
            }
        }
    }
}