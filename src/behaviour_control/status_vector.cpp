#define STATUS_VECTOR_CPP
#include "behaviour_control/status_vector.h"

void initStatusVector(){
    currentSVIndex = 0;

    for(int i=0; i<dim; i++){
        inputs[i] = input();
        datas[i] = data();
    }
}

data getDataAtIndex(int index){
    index = constrain(index, 0, dim-1);
    return datas[index];
}

data getDataAtIndex_backwardsFromCurrent(int steps){
    steps = constrain(steps, 0, dim-1);
    return getDataAtIndex((currentSVIndex-steps+dim) % dim);
}

void updateStatusVector(){
    currentSVIndex = (currentSVIndex+1) % dim;
    CURRENT_DATA_WRITE = CURRENT_DATA_READ;
    CURRENT_INPUT_WRITE = CURRENT_INPUT_READ;
}

