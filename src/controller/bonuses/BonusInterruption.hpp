/**
 * @file BonusInterruption.hpp
 * @brief Déclare le bonus qui duplique la balle (split) et peut interrompre les capsules.
 */
#ifndef BONUS_BONUSINTERRUPTION_HPP
#define BONUS_BONUSINTERRUPTION_HPP

#include "Bonus.hpp"
#include "../GameContext.hpp"

class Ball;

/**
 * @class BonusInterruption
 * @brief Crée des balles supplémentaires en conservant la norme de vitesse.
 */
class BonusInterruption : public Bonus {

public:
    /** Construit le bonus Interruption/Split. */
    BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color);
    BonusInterruption();


    /** Applique l'effet de duplication de balle. */
    void applyEffect(GameContext& gameContext) override;
};

#endif // BONUS_BONUSINTERRUPTION_HPP
