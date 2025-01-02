#include "Paddle.hpp"
#include <allegro5/allegro_primitives.h>
#include "algorithm"


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
void Paddle::move_left(float delta, float boundary_left) {
    center_.x = std::max(center_.x - speed_ * delta, boundary_left + size_.width / 2);

}

void Paddle::move_right(float delta, float boundary_right) {
    center_.x = std::min(center_.x + speed_ * delta, boundary_right - size_.width / 2);
}
void Paddle::update_position(Point &new_position) {


}

void Paddle::collision() {
    // Placeholder collision handling logic
}

Point Paddle::get_position() {
    return center_;
}

Size Paddle:: get_size() {
    return size_;
}


