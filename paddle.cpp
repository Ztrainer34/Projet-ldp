#include "paddle.h"
#include <allegro5/allegro_primitives.h>

Paddle::Paddle(float x, float y, float speed, float width, float height,
               ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor)
    : center_{ x,y }, speed_{speed}, size_{width, height},
      frameColor_{frameColor}, fillColor_{fillColor} {}

void Paddle::draw() {
    float x1 = center_.x - size_.width / 2;  // left edge
    float y1 = center_.y - size_.height / 2; // top edge
    float x2 = center_.x + size_.width / 2;  // right edge
    float y2 = center_.y + size_.height / 2; // bottom edge

    al_draw_filled_rectangle(x1, y1, x2, y2, fillColor_);
    al_draw_rectangle(x1, y1, x2, y2, frameColor_, 1);
}

void Paddle::update_position() {
    // Placeholder logic to update position
    // Actual update logic can be added based on paddle movement.
}

void Paddle::collision() {
    // Placeholder collision handling logic
}

Point Paddle::get_position() {
    return center_;
}

void Paddle::mouseMove(Point mouseLoc) {
    // Placeholder logic for moving the paddle with the mouse
}


