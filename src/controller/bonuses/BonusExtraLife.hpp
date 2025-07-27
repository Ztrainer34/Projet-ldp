#pragma once
#include "Bonus.hpp"
#include "../GameContext.hpp"

class BonusExtraLife : public Bonus {
public:
    BonusExtraLife();
    void applyEffect(GameContext& context) override;
};