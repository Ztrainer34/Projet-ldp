/**
 * @file Capsule.hpp
 * @brief Déclare la capsule qui tombe et transporte un bonus.
 */
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

/**
 * @class Capsule
 * @brief Entité qui tombe depuis une brique et peut être collectée par la raquette.
 */
class Capsule : public Object {
private:
    ALLEGRO_COLOR color_;       // Color of the capsule
    std::shared_ptr<Bonus> bonus_; // Composition : Capsule contient un Bonus
public:
    // Constructor with color
    Capsule(Point position, Size size, bool visible, ALLEGRO_COLOR color, std::shared_ptr<Bonus> bonus);
    Capsule(Point position, Size size, bool visible, ALLEGRO_COLOR color);
    // Existing constructors (deprecated, for compatibility)
    Capsule(Point position, Size size, bool visible, std::shared_ptr<Bonus> bonus) = delete;
    Capsule(Point position, Size size, bool visible) = delete;


    // Updates the capsule's position
    /** Fait tomber la capsule selon une vitesse constante. */
    void updatePosition() override;
    /** Retourne le bonus transporté (peut être nul). */
    std::shared_ptr<Bonus> getBonus() const;
    ALLEGRO_COLOR getColor() const {return color_;};
    /** Détecte la collision avec la raquette. */
    bool checkCollision(Paddle& paddle) const;

};

#endif // CAPSULE_HPP