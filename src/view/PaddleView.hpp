/**
 * @file PaddleView.hpp
 * @brief Vue responsable du dessin de la raquette.
 */
#ifndef PADDLEVIEW_HPP
#define PADDLEVIEW_HPP

#include "../model/Paddle.hpp"
#include "Drawable.hpp"

/**
 * @class PaddleView
 * @brief Dessine une `Paddle` sous forme de rectangle rempli + contour.
 */
class PaddleView : public Drawable {
private:
    const Paddle& paddle;

public:
    PaddleView(const Paddle& p, ALLEGRO_COLOR frame, ALLEGRO_COLOR fill)
        : Drawable(frame, fill), paddle(p) {}

    /** Dessine la raquette selon sa position et sa taille. */
    void draw() override;

    ~PaddleView() override = default;
};

#endif // PADDLEVIEW_HPP
