#include "systems.h"

#define CAMERA_CENTER_X 3
#define CAMERA_CENTER_Y 6

class PositionSysCamera : public PositionSystem{

    public:
        PositionSysCamera();
        void goCenter();
        void update() override;
        void test() override;

};
