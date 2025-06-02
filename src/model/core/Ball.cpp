#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"

#include <allegro5/allegro_primitives.h>
#include <cmath>


Ball::Ball(Point position, Speed speed, float radius,
           ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor)
    : position_{position}, speed_{speed.speed_x, speed.speed_y}, radius_{radius},
      frameColor_{frameColor}, fillColor_{fillColor} {}

Ball::Ball(float x, float y, float speed_x,float speed_y, float radius,
           ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor)
    : position_{x, y}, speed_{speed_x,speed_y}, radius_{radius},
      frameColor_{frameColor}, fillColor_{fillColor} {}


void Ball::updatePosition() {
    // Update the ball's position_ based on speed
    position_.x += speed_.speed_x;
    position_.y += speed_.speed_y;
}

std::vector<Ball> Ball::split() {
    std::vector<Ball> newBalls;

    // init for angles
    float baseSpeedX = speed_.speed_x;
    float baseSpeedY = speed_.speed_y;

    // Create three balls with adjusted directions
    newBalls.emplace_back(position_, Speed(baseSpeedX, baseSpeedY), radius_, frameColor_, fillColor_);
    newBalls.emplace_back(position_, Speed(baseSpeedX - 1.0f, baseSpeedY + 1.0f), radius_, frameColor_, fillColor_);
    newBalls.emplace_back(position_, Speed(baseSpeedX + 1.0f, baseSpeedY - 1.0f), radius_, frameColor_, fillColor_);

    return newBalls;
}

void Ball::handlePaddleCollision(float paddleX, float paddleWidth) {
    // x is the distance of collision point from the left edge of the paddle
    float x = position_.x - (paddleX - paddleWidth / 2);

    // Length L of the paddle
    float L = paddleWidth;

    // Calculate angle alpha (in degrees)
    float alpha = 30 + 120 * (1 - x / L);

    // Convert alpha to radians
    float alpha_radians = alpha * ALLEGRO_PI / 180.0;

    // Update ball's velocity based on the new angle
    speed_.speed_x = speed_.speed_x;
    speed_.speed_y  = -speed_.speed_y;
}


void Ball::handleScreenCollision(float screen_width, float screen_height) {
    // Check collision with left and right walls
    if (position_.x - radius_ < 0) {
        // Hit the left wall
        position_.x = radius_; // Prevent the ball from going out of bounds
        speed_.speed_x = -speed_.speed_x; // Reverse horizontal velocity
    }
    else if (position_.x + radius_ > screen_width) {
        // Hit the right wall
        position_.x = screen_width - radius_; // Prevent the ball from going out of bounds
        speed_.speed_x = -speed_.speed_x; // Reverse horizontal velocity
    }

    // Check collision with top wall
    if (position_.y - radius_ < 0) {
        // Hit the top wall
        position_.y = radius_; // Prevent the ball from going out of bounds
        speed_.speed_y = -speed_.speed_y; // Reverse vertical velocity
    }

    // No action needed for bottom wall in typical Arkanoid-style games, but:
    // If you want to handle bottom wall collision (e.g., lose a life):
    if (position_.y + radius_ > screen_height) {
        // The ball has hit the bottom of the screen (you can handle this as needed)
        // For example: reset ball position_ or decrease player life
    }
}

bool Ball::isTouching(Paddle& paddle) const{
    // Ball boundaries
    float ball_left = position_.x - radius_;
    float ball_right = position_.x + radius_;
    float ball_top = position_.y - radius_;
    float ball_bottom = position_.y + radius_;

    // Paddle boundaries
    float paddle_left = paddle.getPosition().x - paddle.getSize().width / 2;
    float paddle_right = paddle.getPosition().x + paddle.getSize().width / 2;
    float paddle_top = paddle.getPosition().y - paddle.getSize().height / 2;
    float paddle_bottom = paddle.getPosition().y + paddle.getSize().height / 2;

    // Check for overlap
    return ball_right >= paddle_left &&
           ball_left <= paddle_right &&
           ball_bottom >= paddle_top &&
           ball_top <= paddle_bottom;
}
bool Ball::isTouchingScreenBoundary(float screen_width, float screen_height) const {
    return (position_.x - radius_ < 0 || position_.x + radius_ > screen_width ||
            position_.y - radius_ < 0 || position_.y + radius_ > screen_height);
}

// Function to check if the ball is touching a specific brick
// Function to check if the ball is touching a specific brick
bool Ball::isTouchingBrick(const Block& brick) const {
    // Get brick position_ and size
    float brick_left = brick.getPosition().x;
    float brick_right = brick_left + brick.getSize().width;
    float brick_top = brick.getPosition().y;
    float brick_bottom = brick_top + brick.getSize().height;

    // Check if the ball overlaps with the brick
    return (position_.x + radius_ > brick_left &&
            position_.x - radius_ < brick_right &&
            position_.y + radius_ > brick_top &&
            position_.y - radius_ < brick_bottom);
}

bool Ball::IsBallMissed() const {
    bool missed = false;
    if (position_.y < 500) {  // position_ paddle a 550
        missed = true;
    }
    return missed;
}

// Function to handle the collision with a specific brick
void Ball::handleBrickCollision(Block& brick) {
    if (!brick.getVisibility()) return; // Skip invisible bricks

    // Get brick position_ and size
    float brick_left = brick.getPosition().x;
    float brick_right = brick_left + brick.getSize().width;
    float brick_top = brick.getPosition().y;
    float brick_bottom = brick_top + brick.getSize().height;

    // Determine which side of the brick the ball is hitting
    if (position_.y - radius_ < brick_bottom && position_.y + radius_ > brick_top) {
        if (position_.x < brick_left || position_.x > brick_right) {
            speed_.speed_x = -speed_.speed_x; // Reverse horizontal velocity
        } else {
            speed_.speed_y = -speed_.speed_y; // Reverse vertical velocity
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
Speed Ball::getspeed() const {
      return speed_;
}

void Ball::setSpeed(Speed newSpeed){
    speed_ = newSpeed;
}

void Ball::draw() {
    al_draw_filled_circle(position_.x, position_.y, radius_, fillColor_);
    al_draw_circle(position_.x, position_.y, radius_, frameColor_, 1);
}