#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Capsule.hpp"
#include <cmath>
#include "Paddle.hpp"
#include "Bonus.hpp"



Capsule::Capsule(Point position, Size size, bool visible, std::shared_ptr<Bonus> bonus) :
    Object(position, size, visible), bonus_(bonus) {}

Capsule::Capsule(Point position, Size size, bool visible) : Object(position, size, visible) {}



void Capsule::updatePosition() { 
    setY(getY() + C::FALL_SPEED);
}
    


std::shared_ptr<Bonus> Capsule::getBonus() const { return bonus_ ; }

ALLEGRO_COLOR Capsule::getColor() const { return color_; }


bool Capsule::checkCollision(Paddle& paddle) const{
        // Capsule's bounding box
        float capsuleLeft = getX();
        float capsuleRight = getX() + getWidth();
        float capsuleTop = getY();
        float capsuleBottom = getY() + getHeight();

        // Paddle's bounding box
        Point paddlePos = paddle.getPosition();
        Size paddleSize = paddle.getSize();
        float paddleLeft = paddlePos.getX();
        float paddleRight = paddlePos.getX() + paddleSize.getWidth();
        float paddleTop = paddlePos.getY();
        float paddleBottom = paddlePos.getY() + paddleSize.getHeight();

        // Check if capsule is within the paddle's boundaries
        if (capsuleBottom >= paddleTop &&     // Capsule's bottom is at or below the paddle's top
            capsuleTop <= paddleBottom &&     // Capsule's top is at or above the paddle's bottom
            capsuleRight >= paddleLeft &&     // Capsule's right is at or beyond the paddle's left
            capsuleLeft <= paddleRight) {     // Capsule's left is at or before the paddle's right
            return true;                      // Collision detected
            }

        return false;                         // No collision
    }