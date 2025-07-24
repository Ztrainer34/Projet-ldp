#pragma once
#include "../model/Block.hpp"  // Inclure ici, pas dans le .hpp
#include "Drawable.hpp"




class BlockView : public Drawable {
private:
    const Block& block;

public:
    BlockView(const Block& b, ALLEGRO_COLOR frame, ALLEGRO_COLOR fill)
        : Drawable(frame, fill), block(b) {}

    void draw() override;
    
};
