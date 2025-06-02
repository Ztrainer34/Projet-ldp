#include "Block.hpp"
#include "Capsule.hpp"
#include <iostream>
#include <cmath>

#include <allegro5/allegro_primitives.h>

Block::Block(Point position, Size size, ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor,char type)
    : positionBlock(position), sizeBlock(size), frameColor(frameColor), fillColor(fillColor), isVisible(true) {}

void Block::draw() {
    if (isVisible) {
        al_draw_filled_rectangle(positionBlock.x, positionBlock.y,
                                 positionBlock.x + sizeBlock.width,
                                 positionBlock.y + sizeBlock.height,
                                 fillColor);
    }
}
Point Block::getPosition() const {
    return positionBlock;
}

void Block::setPosition(float x, float y) {
    positionBlock.x = x;
    positionBlock.y = y;
}
void Block::setPosition(const Point& new_position) {
    positionBlock = new_position;
}


bool Block::getVisibility() const {
    return isVisible;
}

void Block::setVisibility(bool visibility) {
    isVisible = visibility;
}


ALLEGRO_COLOR Block::getColor() const {
    return fillColor;
}

ALLEGRO_COLOR Block::getFrameColor() const {
    return frameColor;
}
void Block::setFrameColor(ALLEGRO_COLOR& new_color) {
    frameColor = new_color;
}
Size Block::getSize() const {
    return sizeBlock;
}
void Block::setbonus(bool bonus) {
    active = bonus;
}
bool Block::getbonus() const {return active;}
void Block::setCapsule(std::shared_ptr<Capsule> capsule) { capsule_ = capsule; has_capsule_ = true; }
std::shared_ptr<Capsule> Block::getCapsule() const { return capsule_; }
bool Block::hasCapsule() const { return has_capsule_; }
bool Block::colors_are_equals(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2) {
    constexpr float COLOR_EPSILON = 0.001f;
    return (std::fabs(c1.r - c2.r) < COLOR_EPSILON &&
            std::fabs(c1.g - c2.g) < COLOR_EPSILON &&
            std::fabs(c1.b - c2.b) < COLOR_EPSILON &&
            std::fabs(c1.a - c2.a) < COLOR_EPSILON);
}
void Block::destroy(std::vector<std::shared_ptr<Capsule>>& capsules) {
    if (--hitCount_ <= 0) {
        isVisible = false;

        // Add the capsule to the falling list if the block has one
        if (has_capsule_) {
            capsules.push_back(capsule_);
        }
    }
}