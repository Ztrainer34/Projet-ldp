/**
 * @file GoldBlock.hpp
 * @brief Déclare une brique dorée indestructible.
 */
#pragma once

#include "Block.hpp"
#include "../utils/Color.hpp"
/**
 * @class GoldBlock
 * @brief Brique indestructible (HP très élevés), ne donne pas de points.
 */
class GoldBlock : public Block {
private:
    static constexpr int GOLD_HP = 999;
    static constexpr int SCORE_VALUE = 0;
public:
    GoldBlock(Point pos, Size size, bool visible) 
        : Block(pos, size, visible, COLOR_GOLD, GOLD_HP, SCORE_VALUE ) {} // Points de vie "infinis", 0 point

    
    void onHit() override {
        // Ne fait rien, la brique est indestructible.
    }
};