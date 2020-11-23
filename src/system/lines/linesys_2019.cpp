#include "systems/lines/linesys_2019.h"
#include "sensors/sensors.h"

using namespace std;
LineSys2019::LineSys2019() {}
LineSys2019::LineSys2019(vector<DataSource*> in_, vector<DataSource*> out_){
    this->in = in_;
    this->out = out_;

    fboundsX = false;
    fboundsY = false;
    slow = false;

    linesensOldX = 0;
    linesensOldY = 0;

    tookLine = false;

    for(int i = 0; i < 4; i++){
      linetriggerI[i] = 0;
      linetriggerO[i] = 0;
    }

    exitTimer = 0;
    linesens = 0;
}

void LineSys2019::update(){
  inV = 0;
  outV = 0;
  tookLine = false;

  for(DataSource* d : in) d->readSensor();
  for(DataSource* d : out) d->readSensor();

  for(auto it = in.begin(); it != in.end(); it++){
    i = it - in.begin();
    ds = *it;
    linetriggerI[i] = ds->getValue() > LINE_THRESH;
  }
  for(auto it = out.begin(); it != out.end(); it++){
    i = it - out.begin();
    ds = *it;
    linetriggerO[i] = ds->getValue() > LINE_THRESH;
  }

  for(int i = 0; i < 4; i++){
    inV = inV | (linetriggerI[i] << i);
    outV = outV | (linetriggerO[i] << i);
  }


  if ((inV > 0) || (outV > 0)) {
    if(exitTimer > EXTIME) {
      fboundsX = true;
      fboundsY = true;
    }
    exitTimer = 0;
  }

  linesens |= inV | outV;
  outOfBounds();
}

void LineSys2019::outOfBounds(){

  if(fboundsX == true) {
    if(linesens & 0x02) linesensOldX = 2;
    else if(linesens & 0x08) linesensOldX = 8;
    if(linesensOldX != 0) fboundsX = false;
  }
  if(fboundsY == true) {
    if(linesens & 0x01) linesensOldY = 1;
    else if(linesens & 0x04) linesensOldY = 4;
    if(linesensOldY != 0) fboundsY = false;
  }

  if (exitTimer <= EXTIME){
    //fase di rientro
    if(linesens == 15) linesens = linesensOldY | linesensOldX;        //ZOZZATA MAXIMA
    drive->unlockTime = millis();

    if(linesens == 1) outDir = 180;
    else if(linesens == 2) outDir = 270;
    else if(linesens == 4) outDir = 0;
    else if(linesens == 8) outDir = 90;
    else if(linesens == 3) outDir = 225;
    else if(linesens == 6) outDir = 315;
    else if(linesens == 12) outDir = 45;
    else if(linesens == 9) outDir = 135;
    else if(linesens == 7) outDir = 270;
    else if(linesens == 13) outDir = 90;
    else if(linesens == 11) outDir = 180;
    else if(linesens == 14) outDir = 0;
    else if(linesens == 5){
      if(linesensOldX == 2) outDir = 270;
      else if(linesensOldY == 8) outDir = 90;
    }
    else if(linesens == 10){
      if(linesensOldY == 4) outDir = 0;
      else if(linesensOldY == 1) outDir = 180;
    }

    drive->prepareDrive(outDir, LINES_EXIT_SPD);
    tookLine = true;
  }else{
    //fine rientro
    if(linesens == 1) drive->vyp = 1;
    else if(linesens == 2) drive->vxp = 1;
    else if(linesens == 4) drive->vyn = 1;
    else if(linesens == 8) drive->vxn = 1;
    else if(linesens == 3) {
      drive->vyp = 1;
      drive->vxp = 1;
    }
    else if(linesens == 6){
      drive->vxp = 1;
      drive->vyn = 1;
    }
    else if(linesens == 12) {
      drive->vyn = 1;
      drive->vxn = 1;
    }
    else if(linesens == 9) {
      drive->vyp = 1;
      drive->vxn = 1;
    }
    else if(linesens == 7) {
      drive->vyp = 1;
      drive->vyn = 1;
      drive->vxp = 1;
    }
    else if(linesens == 13){
      drive->vxp = 1;
      drive->vxn = 1;
      drive->vyn = 1;
    }
    else if(linesens == 11) {
      drive->vyp = 1;
      drive->vxn = 1;
      drive->vxp = 1;
    }
    else if(linesens == 14) {
      drive->vyn = 1;
      drive->vxn = 1;
      drive->vxp = 1;
    }
    else if(linesens == 5){
      if(linesensOldX == 2) drive->vyp = 1;
      else if(linesensOldY == 8)drive->vyn = 1;
    }
    else if(linesens == 10){
      if(linesensOldY == 4) drive->vyn = 1;
      else if(linesensOldY == 1) drive->vyp = 1;
    }
    drive->canUnlock = true;
    linesens = 0;
    linesensOldY = 0;
    linesensOldX = 0;
  }
}

void LineSys2019::test(){
  update();
  DEBUG.print("In: ");
  for(DataSource* d : in){
      d->update();
      DEBUG.print(d->getValue());
      DEBUG.print(" | ");
  }
  DEBUG.print(" |---| ");
  DEBUG.print("Out: ");
  for(DataSource* d : out){
      d->update();
      DEBUG.print(d->getValue());
      DEBUG.print(" | ");
  }
  DEBUG.println();
  for(int i = 0; i < 4; i++){
    DEBUG.print(linetriggerI[i]);
    DEBUG.print(" | ");
    DEBUG.println(linetriggerO[i]);
  }

  DEBUG.println(inV);
  DEBUG.println(outV);
  DEBUG.println();
}