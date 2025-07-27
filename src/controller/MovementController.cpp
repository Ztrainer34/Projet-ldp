#include "MovementController.hpp"

MovementController::MovementController(GameContext& gameContext) : 
gameContext_(gameContext) {}

void MovementController::update(float delta){
    gameContext_.ball.updatePosition();

    for (auto& capsule : gameContext_.capsules_) {
        if (!capsule->isVisible()) continue;
        capsule->updatePosition();
    }
}

