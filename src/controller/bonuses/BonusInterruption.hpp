#ifndef BONUS_BONUSINTERRUPTION_HPP
#define BONUS_BONUSINTERRUPTION_HPP

#include "Bonus.hpp"
#include "../GameContext.hpp"

class Ball;

class BonusInterruption : public Bonus {

public:
    BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color);
    BonusInterruption();


    void applyEffect(GameContext& gameContext) override;

};

#endif // BONUS_BONUSINTERRUPTION_HPP
