#include "CapsuleView.hpp"


CapsuleView::CapsuleView(const Capsule& l, ALLEGRO_COLOR color)
    : Drawable(color, color), capsule(l) {}

/**
 * @brief si le capsule est actif, on dessine une ligne verticale
 * à sa position.
*/
void CapsuleView::draw() {
    // On ne dessine le capsule que s'il est actif
    if (capsule.isVisible()) {
        const float x = capsule.getX();
        const float y = capsule.getY();
        al_draw_filled_rectangle(x, y, x + capsule.getWidth(), y + capsule.getHeight(), getFillColor());
    }
}