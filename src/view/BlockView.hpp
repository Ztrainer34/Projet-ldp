/**
 * @file BlockView.hpp
 * @brief Vue responsable du dessin d'une brique.
 */
#pragma once
#include "../model/Block.hpp"  // Inclure ici, pas dans le .hpp
#include "Drawable.hpp"


/**
 * @class BlockView
 * @brief Dessine une `Block` si elle est visible.
 */
class BlockView : public Drawable {
private:
    const Block& block;

public:
    BlockView(const Block& b, ALLEGRO_COLOR frame, ALLEGRO_COLOR fill)
        : Drawable(frame, fill), block(b) {}

    /** Dessine le rectangle de la brique si celle-ci est visible. */
    void draw() override;
    
};
