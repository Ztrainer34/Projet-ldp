#include "SilverBlock.hpp"

SilverBlock::SilverBlock(Point pos, Size size, bool visible, int hp) : 
    Block(pos, size, visible, hp) {}

void SilverBlock::onHit() {
    if (hitPoints_ > 0) {
        Block::onHit(); // Réduit les HP de 1
        if (hitPoints_ == 1) {
            // Comportement quand le bloc est sur le point de se briser
            //al_play_sample(bellSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
        }
    }
}