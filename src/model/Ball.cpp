#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"

#include <allegro5/allegro_primitives.h>
#include <cmath>


Ball::Ball(Point position, float radius) 
        : Object(position, Size(radius, radius), Speed(3.0, 3.0)) {}

Ball::Ball(Point position, Speed speed, float radius)
    : Object(position, Size(radius, radius), speed) {}

void Ball::updatePosition() {
    // Update the ball's position_ based on speed
    position_.setPosition(
        getX() + getSpeedX(),
        getY() + getSpeedY()
    );
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

