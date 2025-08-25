/**
 * @file BonusSlow.cpp
 * @brief Implémentation du bonus de ralentissement des balles.
 */

#include "BonusSlow.hpp"

#include "../../model/Ball.hpp"


BonusSlow::BonusSlow(const Point& position,char type, ALLEGRO_COLOR color)
        : Bonus(position, type, color) {}

BonusSlow::BonusSlow() : Bonus() {}

/**
 * @brief Réduit temporairement la vitesse de toutes les balles.
 */
void BonusSlow::applyEffect(GameContext& gameContext){
        // Logique spécifique au bonus "BonusSlow"
        activate(); 

        for(auto& ball : gameContext.ball_){
                ball.setSpeed(Speed(2.0f, 2.0f));
        }
}

/**
 * @brief Restaure la vitesse par défaut des balles.
 */
void BonusSlow::cancelEffect(GameContext& context){
        deactivate();
        for(auto& ball : context.ball_){
                ball.setSpeed(Speed(3.0f, 3.0f));
        }
}


