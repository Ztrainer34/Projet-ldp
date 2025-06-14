// view/BallView.cpp
#include "BallView.hpp"

#include <allegro5/allegro_primitives.h>

void BallView::draw() {

    // Rendu Allegro
    al_draw_filled_circle(ball.getX(), ball.getY(), ball.getRadius(), getFillColor());
    al_draw_circle(ball.getX(), ball.getY(), ball.getRadius(), getFrameColor(), 1);
}