#include "BonusInterruption.hpp"
#include "../../model/Ball.hpp"

BonusInterruption::BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color) {}

BonusInterruption::BonusInterruption() : Bonus() {}

void BonusInterruption::applyEffect(GameContext& gameContext){
    // diviser la ball en 3 et aucun capsule ne peut tomber
    // si ce bonus activé dans le main et visible false pr tte les capsule  pdt le laps de temps
    activate();
    auto threeBalls = gameContext.ball.split(); // divise les ball en 3

}