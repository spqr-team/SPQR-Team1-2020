#pragma once

#include "PID_v2.h"
#include "systems/systems.h"
#include "behaviour_control/complementary_filter.h"

/*Camera translation: because of mechanical imprecision, the center of the camera and the center of the cone mirror may not coincide
To overcome this, each coordinate needs to be shifted by some amount, defined on a per-robot basis that needs to be recalibrated each time.
These values need to be subtracted from the coords used in setMoveSetpoints*/
#define CAMERA_TRANSLATION_X 8
#define CAMERA_TRANSLATION_Y 10
//Camera center: those setpoints correspond to what we consider the center of the field
#define CAMERA_CENTER_X 0
#define CAMERA_CENTER_Y 0

//Camera goal: those setpoints correspond to the position of the center of the goal on the field
#define CAMERA_GOAL_X 0
#define  CAMERA_GOAL_Y -14

#define CAMERA_GOAL_MIN_X -16
#define CAMERA_GOAL_MAX_X 16

#define CAMERA_CENTER_Y_ABS_SUM 60
//Actually it's ± MAX_VAL
#define MAX_X 50
#define MAX_Y (CAMERA_CENTER_Y_ABS_SUM/2)
#define DIST_MULT 1.4

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
        ComplementaryFilter* filterDir;
        ComplementaryFilter* filterSpeed;

};
