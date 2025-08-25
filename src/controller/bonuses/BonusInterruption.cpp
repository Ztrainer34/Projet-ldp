/**
 * @file BonusInterruption.cpp
 * @brief Implémentation du bonus qui duplique la balle en trois.
 */
#include "BonusInterruption.hpp"
#include "../../model/Ball.hpp"
#include <cmath>

BonusInterruption::BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color) {}

BonusInterruption::BonusInterruption() : Bonus() {}

/**
 * @brief Duplique la balle principale en deux supplémentaires en normalisant leur vitesse.
 */
void BonusInterruption::applyEffect(GameContext& gameContext) {
    activate();
    if (gameContext.ball_.empty()) return;

    Ball ball = gameContext.ball_.at(0);

    float vx = ball.getSpeedX();
    float vy = ball.getSpeedY();
    float speed = std::sqrt(vx * vx + vy * vy);
    // Dériver angle de la balle
    float angle = std::atan2(vy, vx); 
    float offset = 0.35f; 

    // Nouvelle balle 2
    Ball ball2 = ball;
    ball2.setSpeed(
        speed * std::cos(angle - offset),
        speed * std::sin(angle - offset)
    );
    // Nouvelle balle 3
    Ball ball3 = ball;
    ball3.setSpeed(
        speed * std::cos(angle + offset),
        speed * std::sin(angle + offset)
    );
    gameContext.ball_.push_back(ball2);
    gameContext.ball_.push_back(ball3);
}
