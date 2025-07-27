#include "BonusExtraLife.hpp"

BonusExtraLife::BonusExtraLife() : Bonus() {
    hasDuration_ = false;
}

void BonusExtraLife::applyEffect(GameContext& context) {
    context.lives++;
}