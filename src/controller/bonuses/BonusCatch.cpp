// BonusCatch.cpp
#include "BonusCatch.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"

BonusCatch::BonusCatch(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color) {}

BonusCatch::BonusCatch() : Bonus() {}

// Appliquer l'effet spécifique au bonus "BonusCatch"
void BonusCatch::applyEffect(GameContext& gameContext) {
    activate(); // Activer le bonus
    Point paddleCenter = gameContext.paddle.getPosition(); // Obtenir la position centrale de la raquette
    
    gameContext.ball.setPosition(paddleCenter); // Positionner la balle au centre de la raquette
    checkDuration();
    // TODO: Ajouter la vérification de la durée dans une capsule de temps
}
