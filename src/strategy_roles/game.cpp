#include "behaviour_control/status_vector.h"
#include "strategy_roles/game.h"
#include "systems/position/positionsys_camera.h"

Game::Game() {}
Game::Game(LineSystem* ls_, PositionSystem* ps_) {
    this->ls = ls_;
    this->ps = ps_;
}

void Game::play(bool condition){
    if(condition) {

        CURRENT_DATA_WRITE.game = this;
        CURRENT_DATA_WRITE.posSystem = (this->ps);
        CURRENT_DATA_WRITE.lineSystem = (this->ls);
        
        ps->update();
        realPlay();
        ls->update();
    }
}