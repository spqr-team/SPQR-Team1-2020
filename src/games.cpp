#define GAMES_CPP

#include "games.h"
#include "linesys_2019.h"
#include "positionsys_zone.h"

void initGames(){
    goalie = new Goalie(new LineSys2019(), new PositionSysZone());
    keeper = new Keeper(new LineSys2019(), new PositionSysZone());
}