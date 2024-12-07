#include "ball.h"
#include <allegro5/allegro_primitives.h>

Ball::Ball(float x, float y, float speed, float radius,
           ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor)
    : position{x, y}, speed{speed}, radius{radius},
      frameColor{frameColor}, fillColor{fillColor} {}

void Ball::update_position() {
    // Update the ball's position based on speed
    position.x += speed;
    position.y += speed;
}

void Ball::collision() {
    // Placeholder for collision logic
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

void Ball::draw() {
    al_draw_filled_circle(position.x, position.y, radius, fillColor);
    al_draw_circle(position.x, position.y, radius, frameColor, 1);
}


