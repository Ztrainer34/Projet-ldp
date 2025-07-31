// BonusCatch.cpp
#include "BonusCatch.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"
#include <iostream>

BonusCatch::BonusCatch(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color), catchActive_(false) {
   
}

BonusCatch::BonusCatch() : Bonus(), catchActive_(false) {
    type_ = 'C'; // Set the correct type for catch bonus
}

// Appliquer l'effet spécifique au bonus "BonusCatch"
void BonusCatch::applyEffect(GameContext& gameContext) {
    std::cout << "[DEBUG] BonusCatch::applyEffect() called!" << std::endl;
    activate(); // Activer le bonus
    catchActive_ = true;
    
    std::cout << "[DEBUG] Catch bonus activated! catchActive_: " << catchActive_ << std::endl;
    
    // Don't immediately catch the ball - just enable the catch ability
    // The ball will be caught when it collides with the paddle
    

}

void BonusCatch::cancelEffect(GameContext& gameContext) {
    std::cout << "[DEBUG] BonusCatch::cancelEffect() called!" << std::endl;
    catchActive_ = false;
    deactivate(); // Deactivate the bonus
    // The ball will continue its normal movement when the bonus expires
}

bool BonusCatch::isCatchActive() const {
    return catchActive_;
}
