/**
 * @file MovementController.hpp
 * @brief Déclare le contrôleur responsable de la mise à jour des positions (balle, capsules, etc.).
 */
#pragma once
#include "../model/Ball.hpp"
#include "../model/Laser.hpp"
#include "../model/Capsule.hpp"
#include "GameContext.hpp"




/**
 * @class MovementController
 * @brief Applique les mises à jour de mouvement pour les entités mobiles.
 */
class MovementController{
private:
    /** Contexte partagé donnant accès aux entités à mettre à jour. */
    GameContext& gameContext_;
   
public:
    /**
     * @brief Construit un contrôleur de mouvements.
     * @param gameContext Contexte de jeu partagé.
     */
    MovementController(GameContext& gameContext);

    /**
     * @brief Met à jour les positions des entités mobiles pour le frame courant.
     * @param delta Temps écoulé depuis la dernière mise à jour (secondes).
     */
    void update();
};
