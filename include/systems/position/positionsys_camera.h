#include "PID_v2.h"

#include "systems/systems.h"

//Note: those variables can be changes, and will need to change depending on camera calibration

//Camera center: those setpoints correspond to the center of the field
#define CAMERA_CENTER_X -10
#define CAMERA_CENTER_Y 20

//Camera goal: those setpoints correspond to the position of the center of the goal on the field
#define CAMERA_GOAL_X 10
#define CAMERA_GOAL_Y 0

#define CAMERA_GOAL_MIN_X -15
#define CAMERA_GOAL_MAX_X 35

#define CAMERA_CENTER_Y_ABS_SUM 60
//Actually it's ± MAX_VAL
#define MAX_X 50
#define MAX_Y (CAMERA_CENTER_Y_ABS_SUM/2)
#define DIST_MULT 1.65

#define Kpx 1
#define Kix 0
#define Kdx 0
#define Kpy 1
#define Kiy 0
#define Kdy 0

class PositionSysCamera : public PositionSystem{

    public:
        PositionSysCamera();
        void goCenter() override;
        void centerGoal() override;
        void setMoveSetpoints(int x, int y);
        void addMoveOnAxis(int x, int y);
        void update() override;
        void test() override;
        void setCameraPID();
        void CameraPID();
        int calcOtherGoalY(int goalY);

        double Inputx, Outputx, Setpointx, Inputy, Outputy, Setpointy;
        int MAX_DIST, vx, vy, axisx, axisy;
        bool givenMovement;
        PID* X;
        PID* Y;

};
