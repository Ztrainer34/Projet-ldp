#include "PaddleController.hpp"
#include <algorithm> // pour std::max/min

PaddleController::PaddleController(Paddle& p, 
                                   std::vector<Laser>& lasers, 
                                   float leftBound, 
                                   float rightBound)
    : paddle_(p), lasers_(lasers),
      boundary_left_(leftBound), boundary_right_(rightBound) {}

void PaddleController::handleInput(const InputState& input, float deltaTime) {
    // Mouvement
    auto pos = paddle_.getPosition();
    if (input.isKeyDown(Key::Left)) {
        pos.x = std::max(boundary_left_ + paddle_.getSize().width/2,
                         pos.x - paddle_.getSpeed() * deltaTime);
    }
    else if (input.isKeyDown(Key::Right)) {
        pos.x = std::min(boundary_right_ - paddle_.getSize().width/2,
                         pos.x + paddle_.getSpeed() * deltaTime);
    }
    paddle_.setPosition(pos);

    // Tir laser
    if (input.isKeyPressed(Key::Space) && paddle_.isLaserModeEnabled()) {
        auto center = paddle_.getPosition();
        lasers_.emplace_back(center.x + paddle_.getSize().width/2,
                             center.y, 400, COLOR_RED);
    }
}

void PaddleController::activateLaserBonus() {
    paddle_.setLaserMode(true);
}
