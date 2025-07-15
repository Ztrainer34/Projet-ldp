#include "SilverBlock.hpp"
#include "../utils/Color.hpp"

SilverBlock::SilverBlock(Point pos, Size size, bool visible) : 
    Block(pos, size, visible, COLOR_SILVER, 2, 200) {}
