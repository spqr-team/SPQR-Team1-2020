#define GAMES_CPP

/* #include "sensors/linesys_2019.h" */
#include "sensors/linesys_camera.h"
#include "position/positionsys_zone.h"
#include "position/positionsys_camera.h"
#include "strategy_roles/games.h"

void initGames(){
    vector<DataSource*> lIn = { new DataSource(S1I, true), new DataSource(S2I, true), new DataSource(S3I, true), new DataSource(S4I, true) };
    vector<DataSource*> lOut = { new DataSource(S1O, true), new DataSource(S2O, true), new DataSource(S3O, true), new DataSource(S4O, true) };

    goalie = new Goalie(new LineSysCamera(lIn, lOut), new PositionSysCamera());
    keeper = new Keeper(new LineSysCamera(lOut, lOut), new PositionSysCamera());
}