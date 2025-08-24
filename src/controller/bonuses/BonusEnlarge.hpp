/**
 * @file BonusEnlarge.hpp
 * @brief Déclare le bonus qui agrandit temporairement la raquette.
 */
#ifndef BONUS_BONUSENLARGE_HPP
#define BONUS_BONUSENLARGE_HPP

#include "Bonus.hpp"
#include "../GameContext.hpp"

class Paddle;

/**
 * @class BonusEnlarge
 * @brief Augmente la largeur de la raquette tant que le bonus est actif.
 */
class BonusEnlarge : public Bonus {

public:
    /** Construit le bonus Enlarge. */
    BonusEnlarge();
    
    /** Applique l'agrandissement de la raquette. */
    void applyEffect(GameContext& gameContext) override;
    /** Annule l'agrandissement (revient à la taille initiale). */
    void cancelEffect(GameContext& context) override;


    
};
#endif // BONUS_BONUSENLARGE_HPP