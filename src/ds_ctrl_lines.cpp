#include "ds_ctrl_lines.h"
#include "sensors.h"

using namespace std;
DSCtrlLines::DSCtrlLines() {}
DSCtrlLines::DSCtrlLines(vector<DataSource*> in_, vector<DataSource*> out_){
    this->in = in_;
    this->out = out_;

    fboundsOX = false;
    fboundsOY = false;
    fboundsX = false;
    fboundsY = false;
    slow = false;

    inVOldX = 0;
    inVOldY = 0;

    for(int i = 0; i < 4; i++){
      linetriggerI[i] = 0;
      linetriggerO[i] = 0;
    }

    exitTimer = 0;
}

void DSCtrlLines::read(){
  inV = 0;
  outV = 0;
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

  inV = inV | outV;
}

void DSCtrlLines::postProcess(){
  if ((inV > 0) || (outV > 0)) {
      fboundsOX = true;
      fboundsOY = true;
    if(exitTimer > EXTIME) {
      fboundsX = true;
      fboundsY = true;
    }
    exitTimer = 0;
  }

  outOfBounds();
}

void DSCtrlLines::outOfBounds(){
    handleExtern();
    handleIntern();
}

void DSCtrlLines::handleIntern(){

  if(fboundsX == true) {
    if(inV & 0x02) inVOldX = 2;
    else if(inV & 0x08) inVOldX = 8;
    if(inVOldX != 0) fboundsX = false;
  }
  if(fboundsY == true) {
    if(inV & 0x01) inVOldY = 1;
    else if(inV & 0x04) inVOldY = 4;
    if(inVOldY != 0) fboundsY = false;
  }
  if (exitTimer <= EXTIME){
    drive->canUnlock = false;
    drive->unlockTime = millis();

    //fase di rientro
    if(inV == 15) {
      inV = inVOldY | inVOldX;        //ZOZZATA MAXIMA
      //digitalWrite(Y, HIGH);
    }

    switch(inV){
      case 1:
        outDir = 180;
        break;
      case 2:
        outDir = 270;
        break;
      case 4:
        outDir = 0;
        break;
      case 8:
        outDir = 90;
        break;
      case 3:
        outDir = 225;
        break;
      case 6:
        outDir = 315;
        break;
      case 12:
        outDir = 45;
        break;
      case 9:
        outDir = 135;
        break;
      case 7:
        outDir = 270;
        break;
      case 13:
        outDir = 90;
        break;
      case 11:
        outDir = 180;
        break;
      case 14:
        outDir = 0;
        break;
      case 5:
        //digitalWrite(R, HIGH);
        if(inVOldX == 2) outDir = 270;
        if(inVOldX == 8) outDir = 90;
        break;
      case 10:
        if(inVOldY == 4) outDir = 0;
        if(inVOldY == 1)outDir = 180;
        break;
      case 15:
        break;
      case 0:
      default:
        //;)
        break;
    }

    if(exitTimer < 45) outVel = 350;
    else outVel = 330;
    drive->prepareDrive(outDir, outVel, 0);
    // keeper_backToGoalPost = true;
    // keeper_tookTimer = true;
  }else{
    inV = 0;
    inVOldX = 0;
    inVOldY = 0;
    // lineSensByteBak = 30;
    drive->canUnlock = true;
  }

//    lineSensByteBak = linesensbyteI;
   if(exitTimer == 99) slow = true;
   else slow = false;
}

void DSCtrlLines::handleExtern(){
    if((outV & 0b00000001) == 1) drive->vyp = 1;  // esclusione
    if((outV & 0b00000100) == 4) drive->vyn = 1;
    if((outV & 0b00000010) == 2) drive->vxp = 1;
    if((outV & 0b00001000) == 8) drive->vxn = 1;
}

void DSCtrlLines::test(){
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