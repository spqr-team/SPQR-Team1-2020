#pragma once

#include "sensors/data_source_camera_vshapedmirror.h"
#include "sensors/sensors.h"
#include "strategy_roles/game.h"

#define X_COORD 10
#define Y_COORD 15

class Spinner : public Game{

    public:
        Spinner();
        Spinner(LineSystem* ls, PositionSystem* ps);

    private:
        void realPlay() override;
        void init() override;
        void circle();
        bool doingCircle = false;
        bool firstCircle = true;        
        bool flag = false;
        unsigned long t =0;

        int step = 0;

        typedef struct v{
            v(){
                x = 0;
                y = 0;
            }
            v(int x_, int y_){
                x = x_;
                y = y_;
            }
            int x, y;
        } spot;

        /*
        spot(13, 15), //top right spot
        spot(-13, 15), //top left spot
        spot(-13, -15) //bottom left spot
        spot(13, -15), //bottom right spot
        */

        vector<spot> spots = {
            /*START: centre*/
            spot(0,0),
            
            // /*1ST BOTTLE*/
            spot(20, 15),
        };

        int current_spot_i = 0;
        spot current_spot;
};
