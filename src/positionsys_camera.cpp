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
    if((camera->true_yb + camera->true_yy) > CAMERA_CENTER_Y) drive->prepareDrive(180, 75, 0);
    else if ((camera->true_yb + camera->true_yy) < -CAMERA_CENTER_Y) drive->prepareDrive(0, 75, 0);
    //X
    else if(camera->true_xb < -CAMERA_CENTER_X || camera->true_xy < -CAMERA_CENTER_X) drive->prepareDrive(90, 75, 0);
    else if(camera->true_xb > CAMERA_CENTER_X || camera->true_xy > CAMERA_CENTER_X) drive->prepareDrive(270, 75, 0);
    else drive->prepareDrive(0, 0, 0);


    /*MAKING A SINGLE LINE HERE, DOESN'T WORK FOR NOW*/
    // int x = 1;
    // int y = 1;
    
    // //Trying using an angle
    // if((CURRENT_DATA_READ.yy) > CAMERA_CENTER_Y || (CURRENT_DATA_READ.yb + CURRENT_DATA_READ.yy) < -CAMERA_CENTER_Y) y = CURRENT_DATA_READ.yb + CURRENT_DATA_READ.yy;
    // if(CURRENT_DATA_READ.bSeen && (CURRENT_DATA_READ.xb < -CAMERA_CENTER_X || CURRENT_DATA_READ.xb > -CAMERA_CENTER_X) ) x = CURRENT_DATA_READ.xb;
    // if(CURRENT_DATA_READ.ySeen && (CURRENT_DATA_READ.xy < -CAMERA_CENTER_X || CURRENT_DATA_READ.xy > -CAMERA_CENTER_X) ) x = CURRENT_DATA_READ.xy;

    // DEBUG.print(x);
    // DEBUG.print(":");
    // DEBUG.println(y);

    // int dir = 90-(atan2(y,x)*180/3.14);
    // dir = (dir+360) % 360;
    // DEBUG.println(dir);
    // drive->prepareDrive(dir, 100, 0);

}