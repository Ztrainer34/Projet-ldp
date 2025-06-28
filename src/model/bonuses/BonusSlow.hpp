#ifndef BONUS_BONUSSLOW_HPP
#define BONUS_BONUSSLOW_HPP

#include "Bonus.hpp"

class Ball;

class BonusSlow : public Bonus {

public:
    BonusSlow(const Point& position,char type, ALLEGRO_COLOR color);
       

    void applyEffect(Ball& ball) override;



    
};
#endif // BONUS_BONUSSLOW_HPP