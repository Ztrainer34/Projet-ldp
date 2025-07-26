
#include "BonusSlow.hpp"

#include "../../model/Ball.hpp"


BonusSlow::BonusSlow(const Point& position,char type, ALLEGRO_COLOR color)
        : Bonus(position, type, color) {}

BonusSlow::BonusSlow() : Bonus() {}

void BonusSlow::applyEffect(BonusContext& bonusContext){
        // Logique spécifique au bonus "BonusSlow"
        activate(); 
        bonusContext.ball.setSpeed(Speed(1.0, 1.0)); // ralentit la balle
        checkDuration();
    }



