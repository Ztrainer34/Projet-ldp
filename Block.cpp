#include "Block.h"
#include <allegro5/allegro_primitives.h>

Block::Block(float x, float y, float width, float height, ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor)
    : position_block{x, y}, size_block{width, height}, frameColor(frameColor), fillColor(fillColor), is_visible(true) {}

void Block::draw() {
    if (is_visible) {
        al_draw_filled_rectangle(position_block.x, position_block.y,
                                 position_block.x + size_block.width,
                                 position_block.y + size_block.height,
                                 fillColor);
    }
}

Point Block::getPosition() const {
    return position_block;
}

void Block::setPosition(float x, float y) {
    position_block.x = x;
    position_block.y = y;
}

void Block::setPosition(const Point& new_position) {
    position_block = new_position;
}

bool Block::getVisibility() const {
    return is_visible;
}

void Block::setVisibility(bool visibility) {
    is_visible = visibility;
}

Size Block::getSize() const {
    return size_block;
}
