#include "PaddleController.hpp"
#include "bonuses/BonusCatch.hpp"
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
        std::cout << "[DEBUG] Spacebar keycode detected!" << std::endl;
        if(paddle_.isLaserModeEnabled()){
            shoot_requested_ = true;
        } else {
            // Check if ball is caught and launch it
            auto& balls = bonusManager_.getGameContext().ball_;
            if (!balls.empty() && balls[0].isCaught()) {
                std::cout << "[DEBUG] Ball is caught, launching it!" << std::endl;
                balls[0].launchBall();
                
                // Reset the catch bonus
                auto& bonus = bonusManager_.getCurrentBonus();
                if (auto catchBonus = std::dynamic_pointer_cast<BonusCatch>(bonus)) {
                    if (catchBonus->isCatchActive()) {
                        std::cout << "[DEBUG] Resetting catch bonus" << std::endl;
                        catchBonus->cancelEffect(bonusManager_.getGameContext());
                    }
                }
            }
            else {
                std::cout << "[DEBUG] Ball is not caught, setting launch_requested_ = true" << std::endl;
                launch_requested_ = true;
            }
        }
    } else {
        std::cout << "[DEBUG] Key pressed but not spacebar: " << keycode << " (ALLEGRO_KEY_SPACE = " << ALLEGRO_KEY_SPACE << ")" << std::endl;
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
    // Mouvement basé sur l'état interne
    if (moving_left_) {
        pos.setX(std::max(boundary_left_, pos.getX() - paddle_.getSpeedX() * deltaTime));
    }
    else if (moving_right_) {
        pos.setX(std::min(boundary_right_ - paddle_.getWidth(), pos.getX() + paddle_.getSpeedX() * deltaTime));
    }
    paddle_.setPosition(pos);

    // Update ball position if it's caught
    auto& balls = bonusManager_.getGameContext().ball_;
    for (auto& ball : balls) {
        if (ball.isCaught()) {
            ball.updateCaughtPosition(paddle_);
        }
    }

    // Tir laser
    if (shoot_requested_ && paddle_.isLaserModeEnabled()) {
        Point start_pos = {paddle_.getX() + paddle_.getWidth() / 2, paddle_.getY()};
        Speed laser_speed = {0, -400};
        lasers_.emplace_back(start_pos, laser_speed);
    }
    
    // Launch ball if catch bonus is active
    if (launch_requested_) {
        std::cout << "[DEBUG] Processing launch_requested_" << std::endl;
        launchBall();
    }
    
    // IMPORTANT : On "consomme" la demande de tir pour qu'il ne se répète pas
    shoot_requested_ = false; 
    launch_requested_ = false;
}

void PaddleController::activateLaserBonus() {
    paddle_.setLaserMode(true);
}

void PaddleController::launchBall() {
    std::cout << "[DEBUG] launchBall() called" << std::endl;
    // Check if any active bonus is a catch bonus
    auto& bonus = bonusManager_.getCurrentBonus();
    std::cout << "[DEBUG] Checking bonus type: " << bonus->get_type() << std::endl;
    if (auto catchBonus = std::dynamic_pointer_cast<BonusCatch>(bonus)) {
        std::cout << "[DEBUG] Found catch bonus, isCatchActive: " << catchBonus->isCatchActive() << std::endl;
        if (catchBonus->isCatchActive()) {
            // Check if ball is currently caught
            auto& balls = bonusManager_.getGameContext().ball_;
            if (!balls.empty()) {
                std::cout << "[DEBUG] Ball is caught: " << balls[0].isCaught() << std::endl;
                if (balls[0].isCaught()) {
                    // Launch the ball
                    std::cout << "[DEBUG] Launching ball!" << std::endl;
                    balls[0].launchBall();
                    return;
                }
            }
        }
        
    std::cout << "[DEBUG] No active catch bonus found for launch" << std::endl;
    }
}
