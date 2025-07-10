#pragma once
#include "../model/Ball.hpp"
#include "../model/Laser.hpp"


class MovementController{
private:
    Ball& ball_; 
    std::vector<Laser>& lasers_ref_; // Une référence vers la liste
public:
    MovementController(Ball& ball, std::vector<Laser>& lasers);

    void update(float delta);
};
