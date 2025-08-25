/**
 * @file MovementController.cpp
 * @brief Implémentation du contrôleur chargé de mettre à jour les mouvements.
 */
#include "MovementController.hpp"

/**
 * @brief Construit le contrôleur de mouvements avec le contexte partagé.
 */
MovementController::MovementController(GameContext& gameContext) : 
gameContext_(gameContext) {}

/**
 * @brief Met à jour les positions des balles et des capsules visibles.
 */
void MovementController::update(){
    for (auto& ball : gameContext_.ball_){
        ball.updatePosition();
    }
    
    for (auto& capsule : gameContext_.capsules_) {
        if (!capsule->isVisible()) continue;
        capsule->updatePosition();
    }
}

