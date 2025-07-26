#ifndef BONUS_BONUSINTERRUPTION_HPP
#define BONUS_BONUSINTERRUPTION_HPP

#include "Bonus.hpp"

class Ball;

class BonusInterruption : public Bonus {

public:
    BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color);

    void applyEffect(Ball &ball) override;


    void update_position() override {
        // Logique pour faire tomber le bonus
        position_.setY(position_.getY() +1); // Exemple : chute verticale
    }

    void draw() const override {
        // Dessiner le bonus "BonusInterrupt" à l'écran
    }

};

#endif // BONUS_BONUSINTERRUPTION_HPP
