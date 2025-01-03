
#include "BonusSlow.hpp"



BonusSlow::BonusSlow(const Point& position, ALLEGRO_COLOR color)
        : Bonus(position, color) {}

void BonusSlow::applyEffect(Ball& ball){
        // Logique spécifique au bonus "BonusSlow"
        activate(); 
        ball.setSpeed(Speed(1.0, 1.0)); // ralentit la balle
        checkDuration();


        // VERIFIER LA DUREE DANS CAPSULE ou MAIN 
    }



