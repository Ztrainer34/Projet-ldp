/**
 * @file BonusExtraLife.hpp
 * @brief Déclare le bonus qui ajoute une vie au joueur.
 */
#pragma once
#include "Bonus.hpp"
#include "../GameContext.hpp"

/**
 * @class BonusExtraLife
 * @brief Incrémente le compteur de vies lors de l'application.
 */
class BonusExtraLife : public Bonus {
public:
    /** Construit le bonus Extra Life. */
    BonusExtraLife();
    /** Applique l'ajout d'une vie au contexte. */
    void applyEffect(GameContext& context) override;
};