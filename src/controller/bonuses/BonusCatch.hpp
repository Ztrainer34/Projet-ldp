#ifndef BONUS_BONUSCATCH_HPP
#define BONUS_BONUSCATCH_HPP

#include "Bonus.hpp"

class Paddle;
class Ball;

class BonusCatch : public Bonus {

public:
    BonusCatch(const Point& position, char type, ALLEGRO_COLOR color);
        

    void update_position() override {
        // Logique pour faire tomber le bonus
        position_.y += 1; // Exemple : chute verticale
    }
    void applyEffect(Paddle& paddle, Ball& ball) override;

    void draw() const override {
        // Dessiner le bonus "BonusCatch" à l'écran
    }

    
};

#endif // BONUS_BONUSCATCH_HPP
