#include "LaserView.hpp"


LaserView::LaserView(const Laser& l, ALLEGRO_COLOR color)
    : Drawable(color, color), laser(l) {}

/**
 * @brief si le laser est actif, on dessine une ligne verticale
 * à sa position.
*/
void LaserView::draw() {
    // On ne dessine le laser que s'il est actif
    if (laser.isActive()) {
        const float x = laser.getX();
        const float y = laser.getY();
        
        // On représente le laser par une simple ligne verticale de 10 pixels de haut
        const float laser_height = 10.0f;

        // On utilise la couleur de remplissage définie dans la classe Drawable
        al_draw_line(x, y, x, y - laser_height, getFillColor(), 2.0f);
    }
}

/**void BonusLaser::draw() const {
    if (active_) {
        al_draw_filled_rectangle(position_.getX(), position_.getY(), 
                                position_.getX() + 2, position_.getY() + 10, color_);
    }
}*/