#include "MovementController.hpp"

MovementController::MovementController(Ball& ball, std::vector<Laser>& lasers) : ball_(ball), lasers_(lasers) {}

void MovementController::update(float delta){
    ball_.updatePosition();
}

