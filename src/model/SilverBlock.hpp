/**
 * @file SilverBlock.hpp
 * @brief Déclare une brique argentée avec points de vie élevés (2).
 */
#pragma once 

#include "Block.hpp"

/**
 * @class SilverBlock
 * @brief Brique préconfigurée de couleur argent, avec 2 HP et score associé.
 */
class SilverBlock : public Block {

public:
    SilverBlock(Point pos, Size size, bool visible); // 2 hp
    
};