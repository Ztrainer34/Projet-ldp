#pragma once 

#include "Block.hpp"

class SilverBlock : Block{

public:
    SilverBlock(Point pos, Size size, bool visible, int hp);
    void onHit() override;
};