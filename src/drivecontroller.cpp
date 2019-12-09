#include "drivecontroller.h"
#include "sensors.h"

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
    errorP = 0;
    errorI = 0;
    errorD = 0;
    
    errorePre = 0;
    pidfactor = 0;
    integral = 0;
}

void DriveController::prepareDrive(int dir=0, int speed=0, int tilt=0){
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

void DriveController::drive(int dir=0, int speed=0, int tilt=0){
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

    m1->drive((int) speed1);
    m2->drive((int) speed2);
    m3->drive((int) speed3);
    m4->drive((int) speed4);
} 