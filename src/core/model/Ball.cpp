#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"

#include <allegro5/allegro_primitives.h>
#include <cmath>


Ball::Ball(Point position, float radius) 
        : Object(position, Size(radius, radius), Speed(0, 0)) {}

Ball::Ball(Point position, Speed speed, float radius)
    : Object(position, speed), radius_(radius) {}

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

void Ball::handlePaddleCollision(float paddleX, float paddleWidth) {
    // x is the distance of collision point from the left edge of the paddle
    float x = getX() - (paddleX - paddleWidth / 2);

    // Length L of the paddle
    float L = paddleWidth;

    // Calculate angle alpha (in degrees)
    float alpha = 30 + 120 * (1 - x / L);

    // Convert alpha to radians
    float alpha_radians = alpha * ALLEGRO_PI / 180.0;

    // Update ball's velocity based on the new angle
    setSpeedY(-getSpeedY());
}


void Ball::handleScreenCollision(float screenWidth, float screenHeight) {
    // Check collision with left and right walls
    if (getX() - radius_ < 0) {
        // Hit the left wall
                 // Prevent the ball from going out of bounds
        setX(radius_);
         // Reverse horizontal velocity
        setSpeedX(-getSpeedX());
    }
    else if (getX() + radius_ > screenWidth) {
        // Hit the right wall
        setX(screenWidth - radius_); // Prevent the ball from going out of bounds
        setSpeedY(-getSpeedY()); // Reverse horizontal velocity
    }

    // Check collision with top wall
    if (getY() - radius_ < 0) {
        // Hit the top wall
        setY(radius_); // Prevent the ball from going out of bounds
        setSpeedY(-getSpeedY()); // Reverse vertical velocity
    }

    // No action needed for bottom wall in typical Arkanoid-style games, but:
    // If you want to handle bottom wall collision (e.g., lose a life):
    if (getY() + radius_ > screenHeight) {
        // The ball has hit the bottom of the screen (you can handle this as needed)
        // For example: reset ball position_ or decrease player life
        //todo !
    }
}

bool Ball::isTouching(Paddle& paddle) const{
    // Ball boundaries
    float ballLeft = getX() - radius_;
    float ballRight = getX() + radius_;
    float ballTop = getY() - radius_;
    float ballBottom = getY() + radius_;

    // Paddle boundaries
    float paddleLeft = paddle.getX() - paddle.getWidth() / 2;
    float paddleRight = paddle.getX() + paddle.getWidth() / 2;
    float paddleTop = paddle.getY() - paddle.getHeight() / 2;
    float paddleBottom = paddle.getY() + paddle.getHeight() / 2;

    // Check for overlap
    return ballRight >= paddleLeft &&
           ballLeft <= paddleRight &&
           ballBottom >= paddleTop &&
           ballTop <= paddleBottom;
}

bool Ball::isTouchingScreenBoundary(float screenWidth, float screenHeight) const {
    return (getX() - radius_ < 0 || getX() + radius_ > screenWidth ||
            getY() - radius_ < 0 || getY() + radius_ > screenHeight);
}

// Function to check if the ball is touching a specific brick
// Function to check if the ball is touching a specific brick
bool Ball::isTouchingBrick(const Block& brick) const {
    // Get brick position_ and size
    float brickLeft = brick.getX();
    float brickRight = brickLeft + brick.getWidth();
    float brickTop = brick.getY();
    float brickBottom = brickTop + brick.getHeight();

    // Check if the ball overlaps with the brick
    return (getX() + radius_ > brickLeft &&
            getX() - radius_ < brickRight &&
            getY() + radius_ > brickTop &&
            getY() - radius_ < brickBottom);
}

bool Ball::IsBallMissed() const {
    bool missed = false;
    if (getY() < CST::SCREEN_BOTTOM_Y) {  // position_ paddle a 550
        missed = true;
    }
    return missed;
}

// Function to handle the collision with a specific brick
void Ball::handleBrickCollision(Block& brick) {
    if (!brick.getVisibility()) return; // Skip invisible bricks

    // Get brick position_ and size
    float brickLeft = brick.getPosition().getX();
    float brickRight = brickLeft + brick.getWidth();
    float brickTop = brick.getPosition().getY();
    float brickBottom = brickTop + brick.getHeight();

    // Determine which side of the brick the ball is hitting
    if (getY() - radius_ < brickBottom && getY() + radius_ > brickTop) {
        if (getX() < brickLeft || getX() > brickRight) {
            setSpeedX(-getSpeedX()); // Reverse horizontal velocity
        } else {
            setSpeedY(-getSpeedY()); // Reverse vertical velocity
        }
    }

    // Mark the brick as no longer visible
    brick.setVisibility(false);
}

float Ball::getRadius() const {
    return radius_;
}

void Ball::setRadius(float new_radius) {
    radius_ = new_radius;
}

