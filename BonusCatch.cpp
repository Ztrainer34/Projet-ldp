// BonusCatch.cpp
#include "BonusCatch.hpp"

BonusCatch::BonusCatch(const Point& position, ALLEGRO_COLOR color) : Bonus(position, color) {}

// Appliquer l'effet spécifique au bonus "BonusCatch"
void BonusCatch::applyEffect(Paddle& paddle, Ball& ball) {
    activate(); // Activer le bonus
    Point paddleCenter = paddle.getPosition(); // Obtenir la position centrale de la raquette
    ball.setPosition(paddleCenter); // Positionner la balle au centre de la raquette

    // TODO: Ajouter la vérification de la durée dans une capsule de temps
}
