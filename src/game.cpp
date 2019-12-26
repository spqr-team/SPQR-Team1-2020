#include "game.h"

Game::Game() {}
Game::Game(LineSystem* ls_, PositionSystem* ps_) {
    this->ls = ls_;
    this->ps = ps_;
}

void Game::play(bool condition){
    ps->update();
    if(condition) realPlay();
    ls->update();

}