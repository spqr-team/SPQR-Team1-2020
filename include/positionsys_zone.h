#pragma once

#include "systems.h"

//POSITION
#define CENTERGOALPOST_VEL1 220
#define CENTERGOALPOST_VEL2 220
#define CENTERGOALPOST_VEL3 220
#define CENTERGOALPOST_CAM_MIN -40
#define CENTERGOALPOST_CAM_MAX 40
#define CENTERGOALPOST_US_MAX 60
#define CENTERGOALPOST_US_CRITIC 25
#define GOCENTER_VEL 280

#define ZONE_MAX_VALUE 150
#define ZONE_LOOP_DECREASE_VALUE 4
#define ZONE_US_UNKNOWN_INCREASE_VALUE 4
#define ZONE_US_INDEX_INCREASE_VALUE 9
#define ZONE_CAM_INCREASE_VALUE 3
#define ZONE_CAM_CENTER_RANGE 25
#define ZONE_LINES_INCREASE_VALUE 100
#define ZONE_LINES_ERROR_VALUE 30

// You can modify this if you need
// LIMITI DEL CAMPO
#define Lx_min 115  // valore minimo accettabile di larghezza
#define Lx_max 195  // valore massimo accettabile di larghezza (larghezza campo)
#define LyF_min 190 // valore minimo accettabile di lunghezza sulle fasce
#define LyF_max 270 // valore massimo accettabile di lunghezza sulle fasce (lunghezza campo)
#define LyP_min 139 // valore minimo accettabile di lunghezza tra le porte
#define LyP_max 250 // valore massimo accettabile di lunghezza tra le porte// con misura x OK con us_dx o us_sx < DxF sto nelle fasce 30 + 30 - 1/2 robot

#define DyF 91     // con misura y OK e robot al CENTER (tra le porte) con us_fx o us_px < DyP sto a NORTH o a SOUTH era - 22
#define DyP 69
#define DxF_Atk 48 // per attaccante, fascia centrale allargata
#define DxF_Def 48 // per portiere, fascia centrale ristretta quEASTa roba viene fatta dentro WhereAmI
#define robot 21   // diametro del robot


// ZONE DEL CAMPO
// codici utilizzabili per una matice 3x3
#define EAST 2
#define WEST 0
#define CENTER 1
#define NORTH 0
#define SOUTH 2

#define NORTH_WEST 1
#define NORTH_CENTER 2
#define NORTH_EAST 3
#define CENTER_WEST 4
#define CENTER_CENTER 5 // codici zona nuovi
#define CENTER_EAST 6
#define SOUTH_WEST 7
#define SOUTH_CENTER 8
#define SOUTH_EAST 9

class PositionSysZone : public PositionSystem{
    public:
        PositionSysZone();
        void update() override;
        void test() override;

        //returns the zone calculated
        int getValue();

    private:
        int zone[3][3];

        int zoneIndex;
        int p;
        int camA;
        int camD;
        unsigned long ao;

        int old_status_x;  // posizione precedente nel campo vale EST, OVEST o CENTRO o 255 >USI FUTURI<
        int old_status_y;  // posizione precedente nel campo vale SUD, NORD o CENTRO o 255 >USI FUTURI<
        bool good_field_x; // vedo tutta la larghezza del campo si/no
        bool good_field_y; // vedo tutta la lunghezza del campo si/no
        int status_x;      // posizione nel campo vale EST, OVEST o CENTRO o 255
        int status_y;      // posizione nel campo vale SUD, NORD o CENTRO o 255
        int guessed_x, guessed_y;
        bool calcPhyZoneCam;
        int DxF;      // con  misura y OK e robot a EST o A OVEST con us_fx o us_px < DyF sto a NORD o a SUD  era - 10
        bool goal_zone;

        //calculations
        void increaseIndex(int, int, int);
        void increaseCol(int, int);
        void increaseRow(int, int);
        void increaseAll(int);
        void decreaseIndex(int, int, int);
        void decreaseCol(int, int);
        void decreaseRow(int, int);
        void decreaseAll(int);
        void increaseRowWithLimit(int, int);
        void increaseColWithLimit(int, int);
        void decreaseRowWithLimit(int, int);
        void decreaseColWithLimit(int, int);

        //reading
        void readPhyZone();
        void phyZoneDirection();
        void phyZoneCam();
        void phyZoneUS();
        void phyZoneLines();

        //testing
        void testPhyZone();
        void testLogicZone();

        //movement
        void goCenter();
        void goGoalPost();
        void centerGoalPost();
        void centerGoalPostCamera(bool);
        void AAANGOLO();
        int diff(int, int);

};