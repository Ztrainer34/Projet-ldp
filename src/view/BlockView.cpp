#include "BlockView.hpp"

void BlockView::draw(){  
    if (block.isVisible()) {
    al_draw_filled_rectangle(block.getX(), block.getY(),
                                block.getX() + block.getWidth(),
                                block.getY() + block.getHeight(),
                                getFillColor());
    }
}
