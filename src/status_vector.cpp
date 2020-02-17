#define STATUS_VECTOR_CPP
#include "status_vector.h"

void initStatusVector(){
    currentSVIndex = 0;

    for(int i=0; i<dim; i++){
        inputs[i] = input();
        datas[i] = data();
    }
}

void updateStatusVector(){
    currentSVIndex = (currentSVIndex+1) % dim;
    CURRENT_DATA_WRITE = CURRENT_DATA_READ;
    CURRENT_INPUT_WRITE = CURRENT_INPUT_READ;
}