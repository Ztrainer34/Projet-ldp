#ifndef BONUS_BONUSSLOW_HPP
#define BONUS_BONUSSLOW_HPP

#include "Bonus.cpp"

class BonusSlow : public Bonus {

public:
    BonusSlow(const Point& position, ALLEGRO_COLOR color);
       

    void applyEffect(Ball& ball) override;


    void update_position() ;

    void draw() const;
};
#endif // BONUS_BONUSSLOW_HPP