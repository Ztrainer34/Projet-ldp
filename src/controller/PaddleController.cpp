#include "PaddleController.hpp"
#include <iostream>


void PaddleController::onKeyDown(int keycode) {
    std::cout << "KeyDown: " << keycode << std::endl;
    if (keycode == ALLEGRO_KEY_A || keycode == ALLEGRO_KEY_Q) {
        moving_left_ = true;
    }
    if (keycode == ALLEGRO_KEY_D || keycode == ALLEGRO_KEY_P) {
        moving_right_ = true;
    }
    if (keycode == ALLEGRO_KEY_SPACE) {
        if(paddle_.isLaserModeEnabled()){
            shoot_requested_ = true;
        }
    }
}

void PaddleController::onKeyUp(int keycode) {
    std::cout << "KeyUp: " << keycode << std::endl;
    if (keycode == ALLEGRO_KEY_A || keycode == ALLEGRO_KEY_Q) {
        moving_left_ = false;
    }
    if (keycode == ALLEGRO_KEY_D || keycode == ALLEGRO_KEY_P) {
        moving_right_ = false;
    }
}

void PaddleController::onMouseMove(float mouseX) {
    float newX = mouseX - paddle_.getWidth() / 2; // Centrer

    // Limites de l'écran
    newX = std::max(boundary_left_, newX);
    newX = std::min(boundary_right_ - paddle_.getWidth(), newX);

    Point currentPos = paddle_.getPosition();
    paddle_.setPosition({newX, currentPos.getY()});
}

void PaddleController::update(float deltaTime) {
    auto pos = paddle_.getPosition();
    std::cout << "Update: posX=" << pos.getX() << ", speedX=" << paddle_.getSpeedX() << ", deltaTime=" << deltaTime << std::endl;
    // Mouvement basé sur l'état interne
    if (moving_left_) {
        pos.setX(std::max(boundary_left_, pos.getX() - paddle_.getSpeedX() * deltaTime));
    }
    else if (moving_right_) {
        pos.setX(std::min(boundary_right_ - paddle_.getWidth(), pos.getX() + paddle_.getSpeedX() * deltaTime));
    }
    std::cout << "New posX=" << pos.getX() << std::endl;
    paddle_.setPosition(pos);

    // Tir laser
    if (shoot_requested_ && paddle_.isLaserModeEnabled()) {
        Point start_pos = {paddle_.getX() + paddle_.getWidth() / 2, paddle_.getY()};
        Speed laser_speed = {0, -400};
        lasers_.emplace_back(start_pos, laser_speed);
    }
    
    // IMPORTANT : On "consomme" la demande de tir pour qu'il ne se répète pas
    shoot_requested_ = false; 
}

void PaddleController::activateLaserBonus() {
    paddle_.setLaserMode(true);
}
