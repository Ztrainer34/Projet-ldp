#include "Ball.hpp"
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <unordered_map>


Ball::Ball(float x, float y, float speed_x,float speed_y, float radius,
           ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor)
    : position{x, y}, speed_{speed_x,speed_y}, radius{radius},
      frameColor{frameColor}, fillColor{fillColor} {}

void Ball::update_position() {
    // Update the ball's position based on speed
    position.x += speed_.speed_x;
    position.y += speed_.speed_y;
}

void Ball::handle_paddle_collision(float paddleX, float paddleWidth) {
    // x is the distance of collision point from the left edge of the paddle
    float x = position.x - (paddleX - paddleWidth / 2);

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


void Ball::handle_screen_collision(float screen_width, float screen_height) {
    // Check collision with left and right walls
    if (position.x - radius < 0) {
        // Hit the left wall
        position.x = radius; // Prevent the ball from going out of bounds
        speed_.speed_x = -speed_.speed_x; // Reverse horizontal velocity
    }
    else if (position.x + radius > screen_width) {
        // Hit the right wall
        position.x = screen_width - radius; // Prevent the ball from going out of bounds
        speed_.speed_x = -speed_.speed_x; // Reverse horizontal velocity
    }

    // Check collision with top wall
    if (position.y - radius < 0) {
        // Hit the top wall
        position.y = radius; // Prevent the ball from going out of bounds
        speed_.speed_y = -speed_.speed_y; // Reverse vertical velocity
    }

    // No action needed for bottom wall in typical Arkanoid-style games, but:
    // If you want to handle bottom wall collision (e.g., lose a life):
    if (position.y + radius > screen_height) {
        // The ball has hit the bottom of the screen (you can handle this as needed)
        // For example: reset ball position or decrease player life
    }
}

bool Ball::is_touching(Paddle& paddle) const{
    // Ball boundaries
    float ball_left = position.x - radius;
    float ball_right = position.x + radius;
    float ball_top = position.y - radius;
    float ball_bottom = position.y + radius;

    // Paddle boundaries
    float paddle_left = paddle.get_position().x - paddle.get_size().width / 2;
    float paddle_right = paddle.get_position().x + paddle.get_size().width / 2;
    float paddle_top = paddle.get_position().y - paddle.get_size().height / 2;
    float paddle_bottom = paddle.get_position().y + paddle.get_size().height / 2;

    // Check for overlap
    return ball_right >= paddle_left &&
           ball_left <= paddle_right &&
           ball_bottom >= paddle_top &&
           ball_top <= paddle_bottom;
}
bool Ball::is_touching_screen_boundary(float screen_width, float screen_height) const {
    return (position.x - radius < 0 || position.x + radius > screen_width ||
            position.y - radius < 0 || position.y + radius > screen_height);
}

// Function to check if the ball is touching a specific brick
// Function to check if the ball is touching a specific brick
bool Ball::is_touching_brick(const Block& brick) const {
    // Get brick position and size
    float brick_left = brick.getPosition().x;
    float brick_right = brick_left + brick.getSize().width;
    float brick_top = brick.getPosition().y;
    float brick_bottom = brick_top + brick.getSize().height;

    // Check if the ball overlaps with the brick
    return (position.x + radius > brick_left &&
            position.x - radius < brick_right &&
            position.y + radius > brick_top &&
            position.y - radius < brick_bottom);
}

bool colors_are_equal(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2) {
    constexpr float COLOR_EPSILON = 0.001f;
    return (std::fabs(c1.r - c2.r) < COLOR_EPSILON &&
            std::fabs(c1.g - c2.g) < COLOR_EPSILON &&
            std::fabs(c1.b - c2.b) < COLOR_EPSILON &&
            std::fabs(c1.a - c2.a) < COLOR_EPSILON);
}

// Function to handle the collision with a specific brick
void Ball::handle_brick_collision(Block& brick) {
    if (!brick.getVisibility()) return; // Skip invisible bricks

    // Get brick position and size
    float brick_left = brick.getPosition().x;
    float brick_right = brick_left + brick.getSize().width;
    float brick_top = brick.getPosition().y;
    float brick_bottom = brick_top + brick.getSize().height;

    // Determine which side of the brick the ball is hitting
    if (position.y - radius < brick_bottom && position.y + radius > brick_top) {
        if (position.x < brick_left || position.x > brick_right) {
            speed_.speed_x = -speed_.speed_x; // Reverse horizontal velocity
        } else {
            speed_.speed_y = -speed_.speed_y; // Reverse vertical velocity
        }
    }


    if (colors_are_equal(brick.getColor(), COLOR_GOLD)) {
        // Gold blocks remain visible
        return;
    }

    static std::unordered_map<Block*, int> silver_hits; // Track hits on silver blocks
    if (colors_are_equal(brick.getColor(), COLOR_SILVER)) {
        silver_hits[&brick]++;

        if (silver_hits[&brick] == 1) {
            // After the first hit, change the outline color to indicate it's been hit once
             // Assuming `Block` has a method for setting outline color
            return; // Silver block stays visible after the first hit
        } else if (silver_hits[&brick] >= 2) {
            silver_hits.erase(&brick); // Remove from tracking after the second hit

        }
    }

    // Mark the block as invisible for all other cases
    brick.setVisibility(false);
}

    // Mark the block as invisible for other colors







    // Mark the brick as no longer visible


Point Ball::getPosition() const {
    return position;
}

void Ball::setPosition(const Point& new_position) {
    position = new_position;
}

float Ball::getRadius() const {
    return radius;
}

void Ball::setRadius(float new_radius) {
    radius = new_radius;
}
speed Ball::getspeed() const {
      return speed_;
}

void Ball::draw() {
    al_draw_filled_circle(position.x, position.y, radius, fillColor);
    al_draw_circle(position.x, position.y, radius, frameColor, 1);
}
