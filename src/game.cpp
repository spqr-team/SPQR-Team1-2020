#include "game.h"

Game::Game() {}

void Game::play(bool condition=true){
    if(condition) realPlay();
}