// view/BallView.hpp
#pragma once
#include "../core/model/Ball.hpp"
#include "Drawable.hpp"

class BallView : public Drawable {
private:
    Ball& ball;

public:
    BallView(Ball& b) : ball(b) {}

    void draw() override;
};
