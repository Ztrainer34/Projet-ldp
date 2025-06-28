// view/BallView.hpp
#pragma once
#include "../model/Ball.hpp"  // Inclure ici, pas dans le .hpp
#include "Drawable.hpp"


class BallView : public Drawable {
private:
    const Ball& ball;

public:
    BallView(const Ball& b, ALLEGRO_COLOR frame, ALLEGRO_COLOR fill) : Drawable(frame, fill), ball(b) {}

    void draw() override;
};
