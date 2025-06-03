
#include "BonusEnlarge.hpp"
#include "Paddle.hpp"


BonusEnlarge::BonusEnlarge(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color) {}

void BonusEnlarge::applyEffect(Paddle& paddle){
        // Logique spécifique au bonus "BonusEnlarge"
        activate(); 
        paddle.enlarge(20);  // agrandir
        checkDuration();

        // VERIFIER LA DUREE DANS CAPSULE ou MAIN 
    }
