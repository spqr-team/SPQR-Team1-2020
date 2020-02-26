#include "positionsys_camera.h"
#include "status_vector.h"
#include "vars.h"
#include "sensors.h"

PositionSysCamera::PositionSysCamera() {}

void PositionSysCamera::update(){
}

void PositionSysCamera::test(){
}

void PositionSysCamera::goCenter(){
    /*WORKS BUT CAN BE BETTER*/
    //Y
    if((CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy) > CAMERA_CENTER_Y) drive->prepareDrive(180, 75, 0);
    else if ((CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy) < -CAMERA_CENTER_Y) drive->prepareDrive(0, 75, 0);
    //X
    else if(CURRENT_DATA_READ.cam_xb < -CAMERA_CENTER_X || CURRENT_DATA_READ.cam_xy < -CAMERA_CENTER_X) drive->prepareDrive(90, 75, 0);
    else if(CURRENT_DATA_READ.cam_xb > CAMERA_CENTER_X || CURRENT_DATA_READ.cam_xy > CAMERA_CENTER_X) drive->prepareDrive(270, 75, 0);
    else drive->prepareDrive(0, 0, 0);


    /*MAKING A SINGLE LINE HERE, DOESN'T WORK FOR NOW*/
    // int x = 1;
    // int y = 1;
    
    // //Trying using an angle
    // if((CURRENT_DATA_READ.cam_yy) > CAMERA_CENTER_Y || (CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy) < -CAMERA_CENTER_Y) 
    // y = CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy;
    // if(CURRENT_DATA_READ.bSeen && (CURRENT_DATA_READ.cam_xb < -CAMERA_CENTER_X || CURRENT_DATA_READ.cam_xb > -CAMERA_CENTER_X) ) x = CURRENT_DATA_READ.cam_xb;
    // if(CURRENT_DATA_READ.ySeen && (CURRENT_DATA_READ.cam_xy < -CAMERA_CENTER_X || CURRENT_DATA_READ.cam_xy > -CAMERA_CENTER_X) ) x = CURRENT_DATA_READ.cam_xy;

    // int dir = -90-(atan2(y*1.5,x)*180/3.14);
    // dir = (dir+360) % 360;
    // drive->prepareDrive(dir, 100, 0);

}