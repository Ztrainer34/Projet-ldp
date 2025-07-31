#ifndef BONUS_BONUSCATCH_HPP
#define BONUS_BONUSCATCH_HPP

#include "Bonus.hpp"
#include "../GameContext.hpp"

class Paddle;
class Ball;

class BonusCatch : public Bonus {
private:
    bool catchActive_; // Flag to track if catch bonus is active

public:
    BonusCatch(const Point& position, char type, ALLEGRO_COLOR color);
    BonusCatch();
        
    void applyEffect(GameContext& gameContext) override;
    void cancelEffect(GameContext& gameContext) override;

    bool isCatchActive() const;
    
};

#endif // BONUS_BONUSCATCH_HPP
