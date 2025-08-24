/**
 * @file BallView.hpp
 * @brief Vue responsable du dessin d'une ou plusieurs balles.
 */
// view/BallView.hpp
#pragma once
#include "../model/Ball.hpp"  // Inclure ici, pas dans le .hpp
#include "Drawable.hpp"


/**
 * @class BallView
 * @brief Dessine un ensemble de `Ball` sous forme de cercles.
 */
class BallView : public Drawable {
private:
    const std::vector<Ball>& balls_;
public:
    BallView(const std::vector<Ball>& balls, ALLEGRO_COLOR frame, ALLEGRO_COLOR fill) : Drawable(frame, fill), balls_(balls) {}

    /** Dessine chaque balle (remplissage + cercle de contour). */
    void draw() override;
};
