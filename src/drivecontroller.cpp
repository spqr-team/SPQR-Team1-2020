#include "drivecontroller.h"
#include "sensors.h"

DriveController::DriveController(Motor* m1_, Motor* m2_, Motor* m3_, Motor* m4_){
    // m1 = new Motor(12, 11, 2, 45);
    // m2 = new Motor(25, 24, 5, 135);
    // m3 = new Motor(27, 26, 6, 225);
    // m4 = new Motor(21, 22, 23, 315);
    this->m1 = m1_;
    this->m2 = m2_;
    this->m3 = m3_;
    this->m4 = m4_;

    for(int i = 0; i < 360; i++){
        sins[i] = (float) sin(i);
        cosins[i] =  (float) cos(i);
    }
}

void DriveController::prepareDrive(int dir, int speed, int tilt){
    pDir = dir;
    pSpeed = speed;
    pTilt = tilt;
}

void DriveController::drivePrepared(){
    drive(pDir, pSpeed, pTilt);
}

void DriveController::drive(int dir, int speed, int tilt){
    vx = ((speed * cosins[dir]));
    vy = ((-speed * sins[dir]));

    speed1 = ((vx * sins[m1->angle] ) + (vy * cosins[m1->angle] ));
    speed2 = ((vx * sins[m2->angle]) + (vy * cosins[m2->angle]));
    speed3 = -(speed1);
    speed4 = -(speed2);

    // calcola l'errore di posizione rispetto allo 0
    delta = compass->getValue();
    if(delta > 180) delta = delta-360;
    delta = delta - tilt;

    // calcola correzione proporzionale
    errorP = KP * delta;

    // calcola correzione derivativa
    errorD = KD * (delta - errorePre);
    errorePre = delta;

    // calcola correzione integrativa
    integral = 0.5 * integral + delta;
    errorI = KI * integral;
    // calcota correzione complessiva
    pidfactor =  errorD + errorP + errorI;               

    speed1 += pidfactor;
    speed2 += pidfactor;
    speed3 += pidfactor;
    speed4 += pidfactor;

    speed1 = constrain(speed1, -255, 255);
    speed2 = constrain(speed2, -255, 255);
    speed3 = constrain(speed3, -255, 255);
    speed4 = constrain(speed4, -255, 255);

    //-almost- eliminating motor deadzones, should increase motor efficiency
    speed1 = (int)speed1 > 0 ? map((int)speed1, 1, 255, 35, 255) : speed1;        
    speed2 = (int)speed2 > 0 ? map((int)speed2, 1, 255, 35, 255) : speed2;        
    speed3 = (int)speed3 > 0 ? map((int)speed3, 1, 255, 35, 255) : speed3;        
    speed4 = (int)speed4 > 0 ? map((int)speed4, 1, 255, 35, 255) : speed4;        

    speed1 = (int)speed1 < 0 ? map((int)speed1, -255, -1, -255, -35) : speed1;        
    speed2 = (int)speed2 < 0 ? map((int)speed2, -255, -1, -255, -35) : speed2;        
    speed3 = (int)speed3 < 0 ? map((int)speed3, -255, -1, -255, -35) : speed3;        
    speed4 = (int)speed4 < 0 ? map((int)speed4, -255, -1, -255, -35) : speed4;        

    m1->drive((int) speed1);
    m2->drive((int) speed2);
    m3->drive((int) speed3);
    m4->drive((int) speed4);
} 