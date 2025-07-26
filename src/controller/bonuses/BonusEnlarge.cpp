
#include "BonusEnlarge.hpp"
#include "../../model/Paddle.hpp"


BonusEnlarge::BonusEnlarge() 
    : Bonus() {}

void BonusEnlarge::applyEffect(BonusContext& bonusContext){
        // Logique spécifique au bonus "BonusEnlarge"
        activate(); 
        bonusContext.paddle.enlarge(20);  // agrandir
        checkDuration();

        // VERIFIER LA DUREE DANS CAPSULE ou MAIN 
    }
