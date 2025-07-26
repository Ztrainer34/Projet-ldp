#ifndef BONUS_BONUSENLARGE_HPP
#define BONUS_BONUSENLARGE_HPP

#include "Bonus.hpp"
#include "BonusContext.hpp"

class Paddle;

class BonusEnlarge : public Bonus {

public:
    BonusEnlarge();
    
    void applyEffect(BonusContext& bonusContext) override;


    
};
#endif // BONUS_BONUSENLARGE_HPP