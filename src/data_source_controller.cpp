#include "data_source_controller.h"

using namespace std;

DataSourceController::DataSourceController() {}
DataSourceController::DataSourceController(vector<DataSource*> ds_){
    this->ds = ds_;
}

void DataSourceController::readSensor(){
    for(DataSource* d : ds){
        d->readSensor();
    }
}
void DataSourceController::update(){
    for(DataSource* d : ds){
        d->update();
    }
}
void DataSourceController::postProcess(){
    for(DataSource* d : ds){
        d->postProcess();
    }
}
void DataSourceController::getValue(){
    for(DataSource* d : ds){
        d->getValue();
    }
}
void DataSourceController::test(){
    DEBUG_PRINT.println("========================================");
    for(DataSource* d : ds){
        d->test();
    }
    DEBUG_PRINT.println("========================================");

}