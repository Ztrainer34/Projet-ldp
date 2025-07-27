
#include "BonusEnlarge.hpp"
#include "../../model/Paddle.hpp"


BonusEnlarge::BonusEnlarge() 
    : Bonus() { hasDuration_ = true; }

void BonusEnlarge::applyEffect(GameContext& GameContext){
    // Logique spécifique au bonus "BonusEnlarge"
        
    activate(); 
    GameContext.paddle.enlarge(20);  // agrandir
    checkDuration();

    // VERIFIER LA DUREE 
}

void BonusEnlarge::cancelEffect(GameContext& context){
    deactivate();
    context.paddle.enlarge(-20);
}