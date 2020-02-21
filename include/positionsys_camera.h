#include "systems.h"

#define CAMERA_CENTER_X 0
#define CAMERA_CENTER_Y 0

class PositionSysCamera : public PositionSystem{

    public:
        PositionSysCamera();
        void goCenter();
        void update() override;
        void test() override;

};
