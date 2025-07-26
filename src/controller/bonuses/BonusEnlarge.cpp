
#include "BonusEnlarge.hpp"
#include "../../model/Paddle.hpp"


BonusEnlarge::BonusEnlarge() 
    : Bonus() {}

void BonusEnlarge::applyEffect(GameContext& GameContext){
        // Logique spécifique au bonus "BonusEnlarge"
        activate(); 
        GameContext.paddle.enlarge(20);  // agrandir
        checkDuration();

        // VERIFIER LA DUREE DANS CAPSULE ou MAIN 
    }
