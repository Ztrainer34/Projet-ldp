/**
 * @file BonusCatch.hpp
 * @brief Déclare le bonus permettant d'attraper temporairement la balle sur la raquette.
 */
#ifndef BONUS_BONUSCATCH_HPP
#define BONUS_BONUSCATCH_HPP

#include "Bonus.hpp"
#include "../GameContext.hpp"

class Paddle;
class Ball;

/**
 * @class BonusCatch
 * @brief Active la capacité de "capturer" la balle à l'impact avec la raquette.
 */
class BonusCatch : public Bonus {
private:
    bool catchActive_; // Flag to track if catch bonus is active

public:
    /**
     * @brief Construit le bonus Catch.
     */
    BonusCatch(const Point& position, char type, ALLEGRO_COLOR color);
    BonusCatch();
        
    /** Applique l'effet Catch au contexte (active le mode capture). */
    void applyEffect(GameContext& gameContext) override;
    /** Annule l'effet Catch (désactive le mode capture). */
    void cancelEffect(GameContext& gameContext) override;

    /** Indique si le mode capture est actif. */
    bool isCatchActive() const;
    
};

#endif // BONUS_BONUSCATCH_HPP
