#ifndef BONUS_BONUSCATCH_HPP
#define BONUS_BONUSCATCH_HPP

#include "Bonus.hpp"
#include "BonusContext.hpp"

class Paddle;
class Ball;

class BonusCatch : public Bonus {

public:
    BonusCatch(const Point& position, char type, ALLEGRO_COLOR color);
    BonusCatch();
        
    void applyEffect(BonusContext& bonusContext) override;

  
    
};

#endif // BONUS_BONUSCATCH_HPP
