#include "drivecontroller.h"
#include "sensors.h"
#include "status_vector.h"

DriveController::DriveController(Motor* m1_, Motor* m2_, Motor* m3_, Motor* m4_){
    m1 = m1_;
    m2 = m2_;
    m3 = m3_;
    m4 = m4_;
    
    for(int i = 0; i < 360; i++){
        sins[i] = (float) sin(torad(i));
        cosins[i] =  (float) cos(torad(i));
    }

    pDir = 0;
    pSpeed = 0;
    pTilt = 0;

    vx = 0;
    vy = 0;

    speed1 = 0;
    speed2 = 0;
    speed3 = 0;
    speed4 = 0;

    delta = 0;
    input = 0;
    output = 0;
    setpoint = 0;

    pid = new PID(&input, &output, &setpoint, KP, KI, KD, 1,DIRECT);

    pid->SetSampleTime(1.5);
    pid->setAngleWrap(true);
    pid->SetDerivativeLag(2);
    pid->SetOutputLimits(-255,255);
    pid->SetMode(AUTOMATIC);

    // Complementary filter for speed
    speedFilter = new ComplementaryFilter(0.3);

    canUnlock = true;
    unlockTime = 0;

    vxp = 0;
    vxn = 0;
    vyp = 0;
    vyn = 0;
}

void DriveController::prepareDrive(int dir, int speed, int tilt){
    pDir = dir;
    pSpeed = speed;
    pTilt = tilt;
}

void DriveController::drivePrepared(){
    drive(pDir, pSpeed, pTilt);
}

float DriveController::torad(float f){
    return (f * PI / 180.0);
}

void DriveController::drive(int dir, int speed, int tilt){

    speed = speedFilter->calculate(speed)*GLOBAL_SPD_MULT;
    tilt = tilt > 180 ? tilt - 360 : tilt;

    vx = ((speed * cosins[dir]));
    vy = ((-speed * sins[dir]));

    if((((vy < 0 && vxn == 1) || (vy > 0 && vxp == 1) || (vx < 0 && vyp == 1) || (vx > 0 && vyn == 1)) && canUnlock) || (millis() > this->unlockTime+UNLOCK_THRESH)) {
        vxn = 0;
        vxp = 0;
        vyp = 0;
        vyn = 0;
    }

    if((vy > 0 && vxn == 1) || (vy < 0 && vxp == 1)) vy = 0;
    if((vx > 0 && vyp == 1) || (vx < 0 && vyn == 1)) vx = 0; 

    speed1 = ((vx * sins[m1->angle] ) + (vy * cosins[m1->angle] ));
    speed2 = ((vx * sins[m2->angle]) + (vy * cosins[m2->angle]));
    speed3 = -(speed1);
    speed4 = -(speed2);

    //  calcola l'errore di posizione rispetto allo 0
    delta = CURRENT_DATA_READ.IMUAngle;
    if(delta > 180) delta = delta - 360;

    input = delta;
    setpoint = tilt;
    
    pid->Compute();

    pidfactor = -output;
    speed1 += pidfactor;
    speed2 += pidfactor;
    speed3 += pidfactor;
    speed4 += pidfactor;

    speed1 = constrain(speed1, -255, 255);
    speed2 = constrain(speed2, -255, 255);
    speed3 = constrain(speed3, -255, 255);
    speed4 = constrain(speed4, -255, 255);     

    m1->drive((int) speed1);
    m2->drive((int) speed2);
    m3->drive((int) speed3);
    m4->drive((int) speed4);

    oldSpeed = speed;

    CURRENT_DATA_WRITE.dir = dir;
    CURRENT_DATA_WRITE.speed = speed;
    CURRENT_DATA_WRITE.tilt = tilt;
    CURRENT_DATA_WRITE.axisBlock[0] = vxp;
    CURRENT_DATA_WRITE.axisBlock[1] = vxn;
    CURRENT_DATA_WRITE.axisBlock[2] = vyp;
    CURRENT_DATA_WRITE.axisBlock[3] = vyn;
} 