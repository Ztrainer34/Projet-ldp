/**
 * @file BlockView.cpp
 * @brief Implémentation du rendu des briques.
 */
#include "BlockView.hpp"

/**
 * @brief Dessine la brique comme un rectangle rempli si elle est visible.
 */
void BlockView::draw(){  
    if (block.isVisible()) {
    al_draw_filled_rectangle(block.getX(), block.getY(),
                                block.getX() + block.getWidth(),
                                block.getY() + block.getHeight(),
                                getFillColor());
    }
}
