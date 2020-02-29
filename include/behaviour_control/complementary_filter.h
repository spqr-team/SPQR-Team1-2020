#include "vars.h"

class ComplementaryFilter{
    public:
        ComplementaryFilter(float k);
        float calculate(float f);
    private:
        int K;
        float oldVal;
};