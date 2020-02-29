#include "behaviour_control/status_vector.h"
#include "strategy_roles/game.h"

Game::Game() {}
Game::Game(LineSystem* ls_, PositionSystem* ps_) {
    this->ls = ls_;
    this->ps = ps_;
}

void Game::play(bool condition){
    ps->update();
    if(condition) {
        realPlay();
        ls->update();

        CURRENT_DATA_WRITE.posSystem = (this->ps);
        CURRENT_DATA_WRITE.lineSystem = (this->ls);
        CURRENT_DATA_WRITE.game = this;

    }
}