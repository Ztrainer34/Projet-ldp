#ifndef BONUS_BONUSENLARGE_HPP
#define BONUS_BONUSENLARGE_HPP

#include "Bonus.hpp"

class Paddle;

class BonusEnlarge : public Bonus {

public:
    BonusEnlarge(const Point& position, char type, ALLEGRO_COLOR color);
       

    void applyEffect(Paddle& paddle) override;


    
};
#endif // BONUS_BONUSENLARGE_HPP