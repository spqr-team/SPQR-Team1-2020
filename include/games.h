#pragma once

#ifdef GAMES_CPP
#define g_extr 
#else
#define g_extr extern
#endif

#include <Arduino.h>
#include "game.h"
#include "goalie.h"
#include "keeper.h"

void initGames();

g_extr Game* goalie;
g_extr Game* keeper;