#pragma once
#include "../model/Ball.hpp"
#include "../model/Laser.hpp"
#include "../model/Capsule.hpp"
#include "GameContext.hpp"




class MovementController{
private:
    GameContext& gameContext_;
   
public:
    MovementController(GameContext& gameContext);

    void update(float delta);
};
