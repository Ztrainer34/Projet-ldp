// view/BallView.hpp
#pragma once
#include "../model/Ball.hpp"  // Inclure ici, pas dans le .hpp
#include "Drawable.hpp"


class BallView : public Drawable {
private:
    const std::vector<Ball>& balls_;
public:
    BallView(const std::vector<Ball>& balls, ALLEGRO_COLOR frame, ALLEGRO_COLOR fill) : Drawable(frame, fill), balls_(balls) {}

    void draw() override;
};
