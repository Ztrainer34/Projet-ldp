#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"

#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream> // Added for debug output


Ball::Ball(Point position, float radius) 
        : Object(position, Size(radius, radius), Speed(3.0f, 3.0f)), radius_(radius), isCaught_(false) {}

Ball::Ball(Point position, Speed speed, float radius)
    : Object(position, Size(radius, radius), speed), radius_(radius), isCaught_(false) {}

void Ball::updatePosition() {
    // Only update position if ball is not caught
    if (!isCaught_) {
        // Update the ball's position_ based on speed
        position_.setPosition(
            getX() + getSpeedX(),
            getY() + getSpeedY()
        );
    }
}

std::vector<Ball> Ball::split() {
    std::vector<Ball> newBalls;

    // init for angles
    float baseSpeedX = getSpeedX();
    float baseSpeedY = getSpeedY();

    // Create three balls with adjusted directions colors dans view
    newBalls.emplace_back(position_, Speed(baseSpeedX, baseSpeedY), radius_);
    newBalls.emplace_back(position_, Speed(baseSpeedX - CST::BALL_SPLIT_OFFSET, 
        baseSpeedY + CST::BALL_SPLIT_OFFSET), radius_);
    newBalls.emplace_back(position_, Speed(baseSpeedX + CST::BALL_SPLIT_OFFSET, 
        baseSpeedY - CST::BALL_SPLIT_OFFSET), radius_);

    return newBalls;
}


bool Ball::IsBallMissed() const {
    bool missed = false;
    if (getY() < CST::SCREEN_BOTTOM_Y) {  // position_ paddle a 550
        missed = true;
    }
    return missed;
}

// Function to handle the collision with a specific brick

float Ball::getRadius() const {
    return radius_;
}

void Ball::setRadius(float new_radius) {
    radius_ = new_radius;
}

void Ball::resetBallPosition(){
    setPosition(CST::SCREEN_WIDTH / 2, 300.0f);
    setSpeed(3.0f,3.0f);
}

void Ball::catchBall(const Paddle& paddle) {
    std::cout << "[DEBUG] Ball::catchBall() called!" << std::endl;
    isCaught_ = true;
    // Position ball in the middle of the paddle
    float paddleCenterX = paddle.getX() + paddle.getWidth() / 2;
    float ballY = paddle.getY() - getRadius(); // Position ball just above the paddle
    setPosition(paddleCenterX, ballY);
    std::cout << "[DEBUG] Ball caught! Position: (" << paddleCenterX << ", " << ballY << ")" << std::endl;
}

void Ball::launchBall() {
    isCaught_ = false;
    // Set a normal launch speed when the ball is released
    setSpeed(3.0f, -3.0f); // Normal speed, launching upward
}

void Ball::updateCaughtPosition(const Paddle& paddle) {
    if (isCaught_) {
        // Update ball position to stay in the middle of the paddle
        float paddleCenterX = paddle.getX() + paddle.getWidth() / 2;
        float ballY = paddle.getY() - getRadius(); // Position ball just above the paddle
        setPosition(paddleCenterX, ballY);
    }
}