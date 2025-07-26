#include "MovementController.hpp"

MovementController::MovementController(Ball& ball, std::vector<Laser>& lasers, std::vector<std::shared_ptr<Capsule>>& capsule) : 
ball_(ball), lasers_(lasers), capsules_(capsule) {}

void MovementController::update(float delta){
    ball_.updatePosition();

    for (auto& capsule : capsules_) {
        if (!capsule->isVisible()) continue;
        capsule->updatePosition();
    }
}

