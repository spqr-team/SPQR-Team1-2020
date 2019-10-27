#include <vars.h>
#include "drive.h"

void DRIVE::initDrive() {
  m.initMot();
}

void DRIVE::drivePID(signed int direzione, float vMot) {
 vx = (vMot * cosin[direzione]);
 vy = (-vMot * sins[direzione]);

 speed1 = ((vx * sins[45] ) + (vy * cosin[45] ));
 speed2 = ((vx * sins[135]) + (vy * cosin[135]));
 speed3 = -(speed1);
 speed4 = -(speed2); 

 pidfactor = misc.updatePID();


 speed1 += pidfactor;
 speed2 += pidfactor;
 speed3 += pidfactor;
 speed4 += pidfactor;

 speed1 = constrain(speed1, -255, 255);
 speed2 = constrain(speed2, -255, 255);
 speed3 = constrain(speed3, -255, 255);
 speed4 = constrain(speed4, -255, 255);

 mot1.mot(1, int(speed1));
 mot2.mot(2, int(speed2));
 mot3.mot(3, int(speed3));
 mot4.mot(4, int(speed4));

 prevPidDir = direzione;
 prevPidSpeed = vMot;
}

void DRIVE::preparePID(int direction, int speed) {
  globalDir = direction;
  globalSpeed = speed;
}