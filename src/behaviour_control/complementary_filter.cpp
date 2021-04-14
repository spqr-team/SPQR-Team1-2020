#include "behaviour_control/complementary_filter.h"

ComplementaryFilter::ComplementaryFilter(float k){
    this->K = k;
    this->oldVal = 0;
}

float result;
float ComplementaryFilter::calculate(float val){
    result = val*K + oldVal*(1-K);
    oldVal = val;
    return result;
}