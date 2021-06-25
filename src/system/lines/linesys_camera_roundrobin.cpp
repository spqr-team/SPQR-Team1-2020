#include "systems/lines/linesys_camera_roundrobin.h"
#include "systems/position/positionsys_camera.h"
#include "sensors/sensors.h"
#include "strategy_roles/games.h"
#include "behaviour_control/status_vector.h"

LineSysCameraRR::LineSysCameraRR(){}
LineSysCameraRR::LineSysCameraRR(vector<DataSource*> in_, vector<DataSource*> out_){
    this->in = in_;
    this->out = out_;

    linesensOldX = 0;
    linesensOldY = 0;

    tookLine = false;

    for(int i = 0; i < 4; i++){
      linetriggerI[i] = 0;
      linetriggerO[i] = 0;
    }
}


void LineSysCameraRR ::update() {
  inV = 0;
  outV = 0;
  tookLine = false;

  for(DataSource* d : in) d->readSensor();
  for(DataSource* d : out) d->readSensor();

  for(auto it = in.begin(); it != in.end(); it++){
    i = it - in.begin();
    ds = *it;
    linetriggerI[i] = ds->getValue() > LINE_THRESH_CAM;
  }
  for(auto it = out.begin(); it != out.end(); it++){
    i = it - out.begin();
    ds = *it;
    linetriggerO[i] = ds->getValue() > LINE_THRESH_CAM;
  }

  for(int i = 0; i < 4; i++){
    inV = inV | (linetriggerI[i] << i);
    outV = outV | (linetriggerO[i] << i);
  }

  tookLine = inV > 0 || outV > 0;
  // if(flag && tookLine) ((PositionSysCamera*)CURRENT_DATA_READ.posSystem)->setMoveSetpoints(0, -8);
}

void LineSysCameraRR::test(){
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