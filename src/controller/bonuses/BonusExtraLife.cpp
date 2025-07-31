#include "BonusExtraLife.hpp"

BonusExtraLife::BonusExtraLife() : Bonus() {
    
}

void BonusExtraLife::applyEffect(GameContext& context) {
    context.lives++;
}