#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Capsule.h"




    Capsule::Capsule(float x, float y, float width, float height, ALLEGRO_COLOR color)
        : x_(x), y_(y), width_(width), height_(height), color_(color), visible_(true) {}

    void Capsule::draw() {
        if (visible_) {
            al_draw_filled_rectangle(x_, y_, x_ + width_, y_ + height_, color_);
        }
    }

    void Capsule::update() {

            y_ += 1; // Move capsule downward
        }


    bool Capsule::isVisible() const { return visible_; }
    void Capsule::setVisible(bool visible) { visible_ = visible; }

    float Capsule::getX() const { return x_; }
    float Capsule::getY() const { return y_; }
    float Capsule::getWidth() const { return width_; }
    float Capsule::getHeight() const { return height_; }
    bool Capsule::checkCollision(Paddle& paddle) const {
        return x_ < paddle.get_position().x + paddle.get_size().width &&
               x_ + width_ > paddle.get_position().x &&
               y_ < paddle.get_position().y + paddle.get_size().height &&
               y_ + height_ > paddle.get_position().y;
    }



