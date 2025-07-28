#include "BonusInterruption.hpp"
#include "../../model/Ball.hpp"

BonusInterruption::BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color) {}

BonusInterruption::BonusInterruption() : Bonus() {hasDuration_ = false;}

void BonusInterruption::applyEffect(GameContext& gameContext){
    // diviser la ball en 3 et aucun capsule ne peut tomber
    // si ce bonus activé dans le main et visible false pr tte les capsule  pdt le laps de temps
    if(gameContext.ball_.empty()) return;
    Ball ball = gameContext.ball_.at(0);
    Ball ball2 = ball;
    Ball ball3 = ball;

    ball2.setSpeedX(ball.getSpeedX()- 50); 


}