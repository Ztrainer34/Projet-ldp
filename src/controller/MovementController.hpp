#pragma once
#include "../model/Ball.hpp"
#include "../model/Laser.hpp"
#include "../model/Capsule.hpp"




class MovementController{
private:
    Ball& ball_; 
    std::vector<Laser>& lasers_; // Une référence vers la liste
    std::vector<std::shared_ptr<Capsule>>& capsules;
public:
    MovementController(Ball& ball, std::vector<Laser>& lasers);

    void update(float delta);
};
