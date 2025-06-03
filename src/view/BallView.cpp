// view/BallView.cpp
#include "BallView.hpp"

#include <allegro5/allegro_primitives.h>

void BallView::draw() {
    // Récupération des données du modèle
    const Point& position = ball.getPosition();
    const float radius = ball.getRadius();
    
    // Choix des couleurs dans la vue
    ALLEGRO_COLOR fillColor = al_map_rgb(255, 0, 0);    // Rouge
    ALLEGRO_COLOR frameColor = al_map_rgb(255, 255, 0); // Jaune
    
    // Rendu Allegro
    al_draw_filled_circle(position.getX(), position.getY(), radius, fillColor);
    al_draw_circle(position.getX(), position.getY(), radius, frameColor, 1);
}