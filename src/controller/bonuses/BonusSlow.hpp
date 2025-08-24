/**
 * @file BonusSlow.hpp
 * @brief Déclare le bonus qui ralentit temporairement les balles.
 */
#ifndef BONUS_BONUSSLOW_HPP
#define BONUS_BONUSSLOW_HPP

#include "Bonus.hpp"
#include "../GameContext.hpp"

class Ball;

/**
 * @class BonusSlow
 * @brief Réduit la vitesse des balles tant que le bonus est actif.
 */
class BonusSlow : public Bonus {

public:
    /** Construit le bonus Slow. */
    BonusSlow(const Point& position,char type, ALLEGRO_COLOR color);
    BonusSlow();

    /** Applique l'effet de ralentissement. */
    void applyEffect(GameContext& gameContext) override;
    /** Annule l'effet de ralentissement. */
    void cancelEffect(GameContext& context) override;
    
};
#endif // BONUS_BONUSSLOW_HPP