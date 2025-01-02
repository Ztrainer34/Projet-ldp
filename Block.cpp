#include "Block.hpp"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>                // Core Allegro functions
#include <allegro5/allegro_font.h>           // Font rendering
#include <allegro5/allegro_primitives.h>     // Drawing shapes
#include <allegro5/allegro_ttf.h>
#include <vector>

Block::Block(float x, float y, float width, float height, ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor,char type)
    : position_block{x, y}, size_block{width, height}, frameColor(frameColor), fillColor(fillColor), is_visible(true),bonus_(type),has_capsule_(false) {}

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

ALLEGRO_COLOR Block::getFrameColor() const {
    return frameColor;
}

Size Block::getSize() const {
    return size_block;
}

ALLEGRO_COLOR Block:: getColor() const  {
    return fillColor;
}

void Block::setFrameColor(ALLEGRO_COLOR& new_color) {
    frameColor = new_color;
}
void Block::setbonus(bool bonus) {
    ative = bonus;
}
bool Block::getbonus() const {return ative;}
void Block::setCapsule(std::shared_ptr<Capsule> capsule) { capsule_ = capsule; has_capsule_ = true; }
std::shared_ptr<Capsule> Block::getCapsule() const { return capsule_; }
bool Block::hasCapsule() const { return has_capsule_; }

void Block::destroy(std::vector<std::shared_ptr<Capsule>>& capsules) {
    if (--hitCount_ <= 0) {
        is_visible = false;

        // Add the capsule to the falling list if the block has one
        if (has_capsule_) {
            capsules.push_back(capsule_);
        }
    }
}


