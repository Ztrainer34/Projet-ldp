#ifndef BONUS_BONUSCATCH_HPP
#define BONUS_BONUSCATCH_HPP

#include "Bonus.hpp"
#include "GameContext.hpp"

class Paddle;
class Ball;

class BonusCatch : public Bonus {

public:
    BonusCatch(const Point& position, char type, ALLEGRO_COLOR color);
    BonusCatch();
        
    void applyEffect(GameContext& gameContext) override;

  
    
};

#endif // BONUS_BONUSCATCH_HPP
