#include "PID_v2.h"
#include "systems.h"

#define CAMERA_CENTER_X 0
#define CAMERA_CENTER_Y -13
#define CAMERA_CENTER_Y_ABS_SUM 72

#define Kpx 1
#define Kix 0
#define Kdx 0
#define Kpy 1
#define Kiy 0
#define Kdy 0

class PositionSysCamera : public PositionSystem{

    public:
        PositionSysCamera();
        void goCenter();
        void update() override;
        void test() override;
        void setCameraPID();
        void CameraPID();
        int calcOtherGoalY(int goalY);

        double Inputx, Outputx, Setpointx, Inputy, Outputy, Setpointy;

        PID* X;
        PID* Y;

};
