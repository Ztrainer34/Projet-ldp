#include "ball.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

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
    speed_.speed_x = speed_.speed_x * cos(alpha_radians)+50;
    speed_.speed_y  = -speed_.speed_y * sin(alpha_radians); // Negative because the ball bounces upward
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
