
#include "BonusSlow.hpp"

#include "../../model/Ball.hpp"


BonusSlow::BonusSlow(const Point& position,char type, ALLEGRO_COLOR color)
        : Bonus(position, type, color) {}

BonusSlow::BonusSlow() : Bonus() {}

void BonusSlow::applyEffect(GameContext& gameContext){
        // Logique spécifique au bonus "BonusSlow"
        activate(); 

        for(auto& ball : gameContext.ball_){
                ball.setSpeed(Speed(1.0f, 1.0f));
        }
}

void BonusSlow::cancelEffect(GameContext& context){
        deactivate();
        for(auto& ball : context.ball_){
                ball.setSpeed(Speed(3.0f, 3.0f));
        }
}


