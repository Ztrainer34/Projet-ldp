#pragma once

#include "Block.hpp"

class GoldBlock : public Block {
public:
    GoldBlock(Point pos, Size size) 
        : Block(pos, size, 999, 0) {} // Points de vie "infinis", 0 point

    // On redéfinit onHit pour qu'elle ne fasse RIEN.
    void onHit() override {
        // Ne fait rien, la brique est indestructible.
    }
};