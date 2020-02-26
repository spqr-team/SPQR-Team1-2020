#include "positionsys_camera.h"
#include "status_vector.h"
#include "vars.h"
#include "sensors.h"

PositionSysCamera::PositionSysCamera() {
    setCameraPID();
}

void PositionSysCamera::update(){
}

void PositionSysCamera::test(){
}

void PositionSysCamera::goCenter(){
    /*WORKS BUT CAN BE BETTER*/
    //Y
    /* if((CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy) > CAMERA_CENTER_Y) drive->prepareDrive(180, 75, 0);
    else if ((CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy) < -CAMERA_CENTER_Y) drive->prepareDrive(0, 75, 0);
    //X
    else if(CURRENT_DATA_READ.cam_xb < -CAMERA_CENTER_X || CURRENT_DATA_READ.cam_xy < -CAMERA_CENTER_X) drive->prepareDrive(90, 75, 0);
    else if(CURRENT_DATA_READ.cam_xb > CAMERA_CENTER_X || CURRENT_DATA_READ.cam_xy > CAMERA_CENTER_X) drive->prepareDrive(270, 75, 0);
    else drive->prepareDrive(0, 0, 0); */


    /*MAKING A SINGLE LINE HERE, DOESN'T WORK FOR NOW*/
    /* int x = 1;
    int y = 1;
    
    //Trying using an angle
    if(CURRENT_DATA_READ.bSeen == true && CURRENT_DATA_READ.ySeen == true){
    if((CURRENT_DATA_READ.cam_yy) > CAMERA_CENTER_Y || (CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy) < -CAMERA_CENTER_Y) 
    y = CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy;
    if(CURRENT_DATA_READ.bSeen && (CURRENT_DATA_READ.cam_xb < -CAMERA_CENTER_X || CURRENT_DATA_READ.cam_xb > -CAMERA_CENTER_X) ) x = CURRENT_DATA_READ.cam_xb;
    if(CURRENT_DATA_READ.ySeen && (CURRENT_DATA_READ.cam_xy < -CAMERA_CENTER_X || CURRENT_DATA_READ.cam_xy > -CAMERA_CENTER_X) ) x = CURRENT_DATA_READ.cam_xy;

    int dir = -90-(atan2(y*1.5,x)*180/3.14);
    dir = (dir+360) % 360;
    drive->prepareDrive(dir, 100, 0);
    } */
    CameraPID();
}

//using a pid controller for the movement, or trying at least
void PositionSysCamera :: setCameraPID(){
    X = new PID(&Inputx, &Outputx, &Setpointx, Kpx, Kix, Kdx, REVERSE);
    X->SetOutputLimits(-50,50);
    X->SetMode(AUTOMATIC);
    X->SetDerivativeLag(1);
    X->SetControllerDirection(DIRECT);
    X->SetSampleTime(1.5);
    Y = new PID(&Inputy, &Outputy, &Setpointy, Kpy, Kiy, Kdy, REVERSE);
    Y->SetOutputLimits(-50,50);
    Y->SetMode(AUTOMATIC);
    Y->SetDerivativeLag(1);
    Y->SetControllerDirection(DIRECT);
    Y->SetSampleTime(1.5);
}

void PositionSysCamera :: CameraPID(){   
    if(CURRENT_DATA_READ.bSeen == true && CURRENT_DATA_READ.ySeen == true){
        Inputx = (CURRENT_DATA_READ.cam_xy + CURRENT_DATA_READ.cam_xb) / 2;
        Inputy = CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy;
        Setpointx = 0;
        Setpointy = 0;
    }
    if (CURRENT_DATA_READ.bSeen == true && CURRENT_DATA_READ.ySeen == false){
        Inputx = CURRENT_DATA_READ.cam_xb;
        Inputy = CURRENT_DATA_READ.cam_yb;
    }
    if (CURRENT_DATA_READ.bSeen == false && CURRENT_DATA_READ.ySeen == true){
        Inputx = CURRENT_DATA_READ.cam_xy;
        Inputy = CURRENT_DATA_READ.cam_yy;
        //Setpointy todo
    }
    //TODO: no goal seen
    X->Compute();
    Y->Compute();
    
    int dir = -90-(atan2(Outputy*1.5,Outputx)*180/3.14);
    dir = (dir+360) % 360;
    if(Outputx > 0) drive->prepareDrive(90, 100, 0);
    else drive->prepareDrive(270, 100, 0);
}