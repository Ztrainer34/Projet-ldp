/**
 * @file Block.cpp
 * @brief Implémentation des briques (construction, capsule, destruction).
 */
#include "Block.hpp"
#include "Capsule.hpp"
#include <iostream>
#include <cmath>

#include <allegro5/allegro_primitives.h>

Block::Block(Point position, Size size, bool visible, ALLEGRO_COLOR color, int hitPoints, int score)
    : Object(position, size, visible), color_(color), hitPoints_(hitPoints), scoreValue_(score) {}

Block::Block(Point position, Size size, bool visible,  int hitPoints)
    : Object(position, size, visible), hitPoints_(hitPoints) {}

/** Active/désactive un état booléen générique. */
void Block::setbonus(bool bonus) {
    active = bonus;
}
bool Block::getbonus() const {return active;}
void Block::setCapsule(std::shared_ptr<Capsule> capsule) { capsule_ = capsule; has_capsule_ = true; }
std::shared_ptr<Capsule> Block::getCapsule() const { return capsule_; }
bool Block::hasCapsule() const { return has_capsule_; }

/**
 * @brief Cache la brique si ses HP sont épuisés, et ajoute sa capsule à la liste fournie.
 */
void Block::destroy(std::vector<std::shared_ptr<Capsule>>& capsules) {
    if (hitPoints_ <= 0) {
        setVisibility(false);

        // Add the capsule to the falling list if the block has one
        if (has_capsule_) {
            capsules.push_back(capsule_);
        }
    }
}