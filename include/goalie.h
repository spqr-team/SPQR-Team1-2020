#pragma once

#include "game.h"

/* #define GOALIE_ATKSPD_LAT  255
#define GOALIE_ATKSPD_BAK  350
#define GOALIE_ATKSPD_FRT  345
#define GOALIE_ATKSPD_STRK 355
#define GOALIE_ATKDIR_PLUSANG1 20
#define GOALIE_ATKDIR_PLUSANG2 35
#define GOALIE_ATKDIR_PLUSANG3 40
#define GOALIE_ATKDIR_PLUSANGBAK 40
#define GOALIE_ATKDIR_PLUSANG1_COR 60
#define GOALIE_ATKDIR_PLUSANG2_COR 70
#define GOALIE_ATKDIR_PLUSANG3_COR 70 */

class Goalie{

    public:
        Goalie();
        void goalie();
        void ballBack(); 
        //void rigore(); to be implemented
         int atk_direction, atk_speed;
};
