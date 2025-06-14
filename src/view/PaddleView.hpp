#ifndef PADDLEVIEW_HPP
#define PADDLEVIEW_HPP

#include "../core/model/Paddle.hpp"
#include "Drawable.hpp"

class PaddleView : public Drawable {
private:
    const Paddle& paddle;

public:
    PaddleView(const Paddle& p, ALLEGRO_COLOR frame, ALLEGRO_COLOR fill)
        : Drawable(frame, fill), paddle(p) {}

    void draw() override;

    ~PaddleView() override = default;
};

#endif // PADDLEVIEW_HPP
