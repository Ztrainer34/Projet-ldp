#include "BonusInterruption.hpp"
#include "Ball.hpp"

BonusInterruption::BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color) {}

void BonusInterruption::applyEffect(Ball& ball){
    // diviser la ball en 3 et aucun capsule ne peut tomber
    // si ce bonus activé dans le main et visible false pr tte les capsule  pdt le laps de temps
    activate();
    auto threeBalls = ball.split(); // divise les ball en 3

}