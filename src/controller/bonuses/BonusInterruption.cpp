#include "BonusInterruption.hpp"
#include "../../model/Ball.hpp"
#include <cmath>

BonusInterruption::BonusInterruption(const Point& position, char type, ALLEGRO_COLOR color)
    : Bonus(position, type, color) {}

BonusInterruption::BonusInterruption() : Bonus() {}

void BonusInterruption::applyEffect(GameContext& gameContext){
    // diviser la ball en 3 et aucun capsule ne peut tomber
    // si ce bonus activé dans le main et visible false pr tte les capsule  pdt le laps de temps
    activate();
    if(gameContext.ball_.empty()) return;
    Ball ball = gameContext.ball_.at(0);
    Ball ball2 = ball;
    Ball ball3 = ball;
    //changer orientation
    ball2.setSpeedX(ball.getSpeedX()- 50.0f); 
    ball3.setSpeedX(ball.getSpeedX()+ 50.0f);
    // normalize speeds of the two new balls to match the original ball's speed magnitude
    const float originalVx = ball.getSpeedX();
    const float originalVy = ball.getSpeedY();
    const float targetSpeed = std::sqrt(originalVx * originalVx + originalVy * originalVy);

    float vx2 = ball2.getSpeedX();
    float vy2 = ball2.getSpeedY();
    float speed2 = std::sqrt(vx2 * vx2 + vy2 * vy2);
    if (speed2 > 0.0f) {
        float scale2 = targetSpeed / speed2;
        ball2.setSpeed(vx2 * scale2, vy2 * scale2);
    }

    float vx3 = ball3.getSpeedX();
    float vy3 = ball3.getSpeedY();
    float speed3 = std::sqrt(vx3 * vx3 + vy3 * vy3);
    if (speed3 > 0.0f) {
        float scale3 = targetSpeed / speed3;
        ball3.setSpeed(vx3 * scale3, vy3 * scale3);
    }

    gameContext.ball_.push_back(ball2); 
    gameContext.ball_.push_back(ball3); 

}