/**
 * @file BallView.cpp
 * @brief Implémentation du rendu des balles.
 */
// view/BallView.cpp
#include "BallView.hpp"

#include <allegro5/allegro_primitives.h>

/**
 * @brief Pour chaque balle, dessine un cercle rempli et un contour.
 */
void BallView::draw() {
     for (const auto& ball : balls_) {
        al_draw_filled_circle(ball.getX(), ball.getY(), ball.getRadius(), getFillColor());
        al_draw_circle(ball.getX(), ball.getY(), ball.getRadius(), getFrameColor(), 1);
    }
}