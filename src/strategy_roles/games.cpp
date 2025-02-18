#define GAMES_CPP

/* #include "sensors/linesys_2019.h" */
#include "systems/lines/linesys_camera.h"
#include "systems/lines/linesys_camera_roundrobin.h"
#include "systems/systems.h"
#include "systems/position/positionsys_zone.h"
#include "systems/position/positionsys_camera.h"
#include "strategy_roles/games.h"

void initGames(){
    vector<DataSource*> lIn = { new DataSource(S1I, true), new DataSource(S2I, true), new DataSource(S3I, true), new DataSource(S4I, true) };
    vector<DataSource*> lOut = { new DataSource(S1O, true), new DataSource(S2O, true), new DataSource(S3O, true), new DataSource(S4O, true) };

    // striker_test = new StrikerTest(new LineSysCamera(lIn, lOut), new PositionSysCamera());
    striker = new Striker(new LineSysCamera(lIn, lOut), new PositionSysCamera());
    pass_and_shoot = new PassAndShoot(new LineSysCamera(lIn, lOut), new PositionSysCamera());
    precision_shooter = new PrecisionShooter(new LineSysCamera(lIn, lOut), new PositionSysCamera());
    striker_roller = new StrikerRoller(new LineSysCamera(lIn, lOut), new PositionSysCamera());

    tc1 = new StrikerRoller(new LineSystemEmpty(), new PositionSysCamera());
    tc2 = new RoundRobin(new LineSysCameraRR(lIn, lOut), new PositionSysCamera());
    
    tc3_1 = new CornerKick(new LineSystemEmpty(), new PositionSysCamera());
    tc3_2 = new CornerKick2(new LineSystemEmpty(), new PositionSysCamera());
    
    st_tc1 = new SpotFinder(new LineSystemEmpty(), new PositionSysCamera());
    st_tc3 = new Spinner(new LineSystemEmpty(), new PositionSysCamera());
    // keeper = new Keeper(new LineSysCamera(lOut, lOut), new PositionSysCamera());
}