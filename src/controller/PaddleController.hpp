#pragma once
#include <algorithm> // pour std::max/min
#include <allegro5/allegro.h> 
#include "../model/Paddle.hpp"


class PaddleController {
private:
    Paddle& paddle_;
    std::vector<Laser>& lasers_;
    float boundary_left_;
    float boundary_right_;

    bool moving_left_ = false;
    bool moving_right_ = false;
    bool shoot_requested_ = false;


public:
    PaddleController(Paddle& p, std::vector<Laser>& l,
                     float left, float right)
      : paddle_(p), lasers_(l),
        boundary_left_(left), boundary_right_(right) {}

    // Méthodes pour que la boucle main nous informe des événements
    void onKeyDown(int keycode);
    void onKeyUp(int keycode);
    void onMouseMove(float mouseX);
    void update(float deltaTime);

    void activateLaserBonus();
};
