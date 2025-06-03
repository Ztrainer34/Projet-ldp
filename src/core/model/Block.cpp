#include "Block.hpp"
#include "Capsule.hpp"
#include <iostream>
#include <cmath>

#include <allegro5/allegro_primitives.h>

Block::Block(Point position, Size size, bool visible, char type)
    : Object(position, size, visible), type_(type) {}


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
        setVisibility(false);

        // Add the capsule to the falling list if the block has one
        if (has_capsule_) {
            capsules.push_back(capsule_);
        }
    }
}