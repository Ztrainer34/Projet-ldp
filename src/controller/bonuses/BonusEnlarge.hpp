#ifndef BONUS_BONUSENLARGE_HPP
#define BONUS_BONUSENLARGE_HPP

#include "Bonus.hpp"
#include "../GameContext.hpp"

class Paddle;

class BonusEnlarge : public Bonus {

public:
    BonusEnlarge();
    
    void applyEffect(GameContext& gameContext) override;
    void cancelEffect(GameContext& context) override;


    
};
#endif // BONUS_BONUSENLARGE_HPP