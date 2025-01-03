#ifndef BONUS_BONUSINTERRUPT_HPP
#define BONUS_BONUSINTERRUPT_HPP

#include "Bonus.h"

class BonusInterrupt : public Bonus {

public:
    BonusInterrupt(const Point& position, ALLEGRO_COLOR color);
        : Bonus(position_, color_) {}

    void applyEffect(Ball &ball) override;

    void update_position() override {
        // Logique pour faire tomber le bonus
        position_.y += 1; // Exemple : chute verticale
    }

    void draw() const override {
        // Dessiner le bonus "BonusInterrupt" à l'écran
    }

};

#endif // BONUS_BONUSINTERRUPT_HPP
