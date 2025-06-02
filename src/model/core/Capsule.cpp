#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Capsule.hpp"
#include <cmath>
#include "Paddle.hpp"
#include "Bonus.hpp"




Capsule::Capsule(float x, float y, float width, float height, ALLEGRO_COLOR color, std::shared_ptr<Bonus> bonus)
        : x_(x), y_(y), width_(width), height_(height), color_(color), visible_(true), bonus_(bonus) {}

Capsule::Capsule(Point position, Size size, ALLEGRO_COLOR color, std::shared_ptr<Bonus> bonus) :
    position_{position}, size_{size}, color_{color}, visible_(true), bonus_(bonus) {}

Capsule::Capsule(Point position, Size size, ALLEGRO_COLOR color) : 
position_{position}, size_{size}, color_{color}, visible_(true) {}


    void Capsule::draw() {
        if (visible_) {
            al_draw_filled_rectangle(x_, y_, x_ + width_, y_ + height_, color_);
        }
    }

    void Capsule::update() {

            y_ += 1; // Move capsule downward
        }
    

bool Capsule::colors_are_equals(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2) {
        constexpr float COLOR_EPSILON = 0.001f;
        return (std::fabs(c1.r - c2.r) < COLOR_EPSILON &&
                std::fabs(c1.g - c2.g) < COLOR_EPSILON &&
                std::fabs(c1.b - c2.b) < COLOR_EPSILON &&
                std::fabs(c1.a - c2.a) < COLOR_EPSILON);
    }

bool Capsule::isVisible() const { return visible_; }
void Capsule::setVisible(bool visible) { visible_ = visible; }

float Capsule::getX() const { return x_; }
float Capsule::getY() const { return y_; }

float Capsule::getWidth() const { return width_; }
float Capsule::getHeight() const { return height_; }

std::shared_ptr<Bonus> Capsule::getBonus() const { return bonus_ ; }

ALLEGRO_COLOR Capsule::getColor() const { return color_; }


bool Capsule::checkCollision(Paddle& paddle) const{
        // Capsule's bounding box
        float capsuleLeft = x_;
        float capsuleRight = x_ + width_;
        float capsuleTop = y_;
        float capsuleBottom = y_ + height_;

        // Paddle's bounding box
        Point paddlePos = paddle.getPosition();
        Size paddleSize = paddle.getSize();
        float paddleLeft = paddlePos.x;
        float paddleRight = paddlePos.x + paddleSize.width;
        float paddleTop = paddlePos.y;
        float paddleBottom = paddlePos.y + paddleSize.height;

        // Check if capsule is within the paddle's boundaries
        if (capsuleBottom >= paddleTop &&     // Capsule's bottom is at or below the paddle's top
            capsuleTop <= paddleBottom &&     // Capsule's top is at or above the paddle's bottom
            capsuleRight >= paddleLeft &&     // Capsule's right is at or beyond the paddle's left
            capsuleLeft <= paddleRight) {     // Capsule's left is at or before the paddle's right
            return true;                      // Collision detected
            }

        return false;                         // No collision
    }