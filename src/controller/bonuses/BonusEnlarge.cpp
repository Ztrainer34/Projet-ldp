
#include "BonusEnlarge.hpp"
#include "../../model/Paddle.hpp"


BonusEnlarge::BonusEnlarge() 
    : Bonus() { }

void BonusEnlarge::applyEffect(GameContext& GameContext){
    // Logique spécifique au bonus "BonusEnlarge"
    activate(); 
    GameContext.paddle.enlarge(50);  // agrandir
}

void BonusEnlarge::cancelEffect(GameContext& context){
    deactivate();
    context.paddle.enlarge(-50); // Subtract the same amount that was added
}