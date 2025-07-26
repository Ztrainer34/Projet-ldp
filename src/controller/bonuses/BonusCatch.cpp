// BonusCatch.cpp
#include "BonusCatch.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"

BonusCatch::BonusCatch(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color) {}

// Appliquer l'effet spécifique au bonus "BonusCatch"
void BonusCatch::applyEffect(Paddle& paddle, Ball& ball) {
    activate(); // Activer le bonus
    Point paddleCenter = paddle.getPosition(); // Obtenir la position centrale de la raquette
    ball.setPosition(paddleCenter); // Positionner la balle au centre de la raquette
    checkDuration();
    // TODO: Ajouter la vérification de la durée dans une capsule de temps
}
