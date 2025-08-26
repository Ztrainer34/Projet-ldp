/**
 * @file BonusEnlarge.cpp
 * @brief Implémentation du bonus d'agrandissement de la raquette.
 */

#include "BonusEnlarge.hpp"
#include "../../model/Paddle.hpp"
#include "../../utils/Constants.hpp"

BonusEnlarge::BonusEnlarge() 
    : Bonus() { }

/**
 * @brief Agrandit temporairement la raquette.
 */
void BonusEnlarge::applyEffect(GameContext& GameContext){
    // Logique spécifique au bonus "BonusEnlarge"
    activate(); 
    GameContext.paddle.enlarge(Constants::PADDLE_FACTOR_ENLARGE);  // agrandir
}

/**
 * @brief Annule l'agrandissement de la raquette.
 */
void BonusEnlarge::cancelEffect(GameContext& context){
    deactivate();
    context.paddle.enlarge(-Constants::PADDLE_FACTOR_ENLARGE); // Subtract the same amount that was added
}