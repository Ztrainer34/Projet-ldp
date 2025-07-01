#ifndef CAPSULE_HPP
#define CAPSULE_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "Object.hpp"

namespace C = Constants;

// Déclarations anticipées
class Paddle;
class Bonus;


class Capsule : public Object {
private:
    ALLEGRO_COLOR color_;       // Color of the capsule
    std::shared_ptr<Bonus> bonus_; // Composition : Capsule contient un Bonus
public:
    // Constructor
    // Nouveau constructeur sans bonus
    Capsule(Point position, Size size, bool visible, std::shared_ptr<Bonus> bonus);
    Capsule(Point position, Size size, bool visible);


    // Updates the capsule's position
    void updatePosition() override;
    std::shared_ptr<Bonus> getBonus() const;

    bool checkCollision(Paddle& paddle) const;

};

#endif // CAPSULE_HPP