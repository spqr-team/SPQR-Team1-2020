#include "complementary_filter.h"

ComplementaryFilter::ComplementaryFilter(float k){
    this->K = k;
}

float result;
float ComplementaryFilter::calculate(float val){
    result = val*K + oldVal*(1-K);
    oldVal = val;
    return result;
}