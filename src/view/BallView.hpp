// view/BallView.hpp
#pragma once
#include "../core/model/Ball.hpp"  // Inclure ici, pas dans le .hpp
#include "Drawable.hpp"




class BallView : public Drawable {
private:
    const Ball& ball;

public:
    BallView(const Ball& b) : ball(b) {}

    void draw() override;
};
