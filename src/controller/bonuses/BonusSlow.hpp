#ifndef BONUS_BONUSSLOW_HPP
#define BONUS_BONUSSLOW_HPP

#include "Bonus.hpp"
#include "BonusContext.hpp"

class Ball;

class BonusSlow : public Bonus {

public:
    BonusSlow(const Point& position,char type, ALLEGRO_COLOR color);
    BonusSlow();

    void applyEffect(BonusContext& bonusContext) override;



    
};
#endif // BONUS_BONUSSLOW_HPP