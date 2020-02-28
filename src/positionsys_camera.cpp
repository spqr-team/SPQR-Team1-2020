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
    ;
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
    MAX_DIST = sqrt(MAX_X*MAX_X + MAX_Y*MAX_Y);
    Inputx = 0;
    Outputx = 0;
    Setpointx = 0;
    Inputy = 0;
    Outputy = 0;
    Setpointy = 0;
    
    X = new PID(&Inputx, &Outputx, &Setpointx, Kpx, Kix, Kdx, DIRECT);
    X->SetOutputLimits(-50,50);
    X->SetMode(AUTOMATIC);
    X->SetDerivativeLag(1);
    X->SetSampleTime(2);
    Y = new PID(&Inputy, &Outputy, &Setpointy, Kpy, Kiy, Kdy, DIRECT);
    Y->SetOutputLimits(-50,50);
    Y->SetMode(AUTOMATIC);
    Y->SetDerivativeLag(1);
    Y->SetSampleTime(2);
}

/*Knowing the sum of the absolute values of the y position of the goals, it calculates the missing goal y knowing the other one
We know the sum of the absolute values is a fixed number.
By♦ subtracting the absolute value of the goal y we know to the sum of the absolute values, we get the absolute value of the missing goal y
The sign of the goal y we found is simply the reverse of the one we got
*/
int PositionSysCamera::calcOtherGoalY(int goalY){
    int otherGoalY = CAMERA_CENTER_Y_ABS_SUM - abs(goalY);
    otherGoalY = goalY < 0 ? otherGoalY : -otherGoalY;
    return otherGoalY;
}

void PositionSysCamera :: CameraPID(){   
    if(CURRENT_DATA_READ.bSeen == true && CURRENT_DATA_READ.ySeen == true){
        Inputx = (CURRENT_DATA_READ.cam_xy + CURRENT_DATA_READ.cam_xb) / 2;
        Inputy = CURRENT_DATA_READ.cam_yb + CURRENT_DATA_READ.cam_yy;
    }else if (CURRENT_DATA_READ.bSeen == true && CURRENT_DATA_READ.ySeen == false){
        Inputx = CURRENT_DATA_READ.cam_xb;
        Inputy = CURRENT_DATA_READ.cam_yb + calcOtherGoalY(CURRENT_DATA_READ.cam_yb);
    }else if (CURRENT_DATA_READ.bSeen == false && CURRENT_DATA_READ.ySeen == true){
        Inputx = CURRENT_DATA_READ.cam_xy;
        Inputy = CURRENT_DATA_READ.cam_yy + calcOtherGoalY(CURRENT_DATA_READ.cam_yy);
        //Setpointy todo
    }else{
        //TODO: no goal seen
    }
    Setpointx = CAMERA_CENTER_X;
    Setpointy = CAMERA_CENTER_Y;
        
    X->Compute();
    Y->Compute();
    
    // DEBUG.print(CURRENT_DATA_READ.cam_yb);
    // DEBUG.print(" ");
    // DEBUG.println(calcOtherGoalY(CURRENT_DATA_READ.cam_yb));

    /*if(abs(Outputx) <= 1 && abs(Outputy) <= 1){
        drive->prepareDrive(0,0,0);
    }else{*/
        int dir = -90-(atan2(-Outputy,-Outputx)*180/3.14);
        dir = (dir+360) % 360;

        int dist = sqrt(Outputx*Outputx + Outputy*Outputy);
        int speed = map(dist*DIST_MULT, 0, MAX_DIST, 0, 350);
        drive->prepareDrive(dir, speed, 0);
        //DEBUG.println(dir);
    //}
}