#ifndef BONUS_BONUSINTERRUPTION_HPP
#define BONUS_BONUSINTERRUPTION_HPP

#include "Bonus.hpp"
#include "BonusContext.hpp"

class Ball;

class BonusInterruption : public Bonus {

public:
    BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color);
    BonusInterruption();


    void applyEffect(BonusContext& bonusContext) override;

};

#endif // BONUS_BONUSINTERRUPTION_HPP
