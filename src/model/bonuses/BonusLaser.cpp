#include "BonusLaser.hpp"
#include <allegro5/allegro_primitives.h>
#include "Block.hpp"
#include "Capsule.hpp"
#include "Paddle.hpp"
#include "Level.hpp"

// Constructeur
BonusLaser::BonusLaser(float x, float y, float speed, ALLEGRO_COLOR color)
    : Bonus(Point(x, y), color), position_(x, y), speed_(speed), color_(color), active_(true) {}

// Mise à jour de la position du bonuslaser
void BonusLaser::update(float deltaTime) {
    position_.y -= speed_ * deltaTime; // Le bonuslaser monte vers le haut
    if (position_.y < 0) {
        active_ = false; // Désactiver le bonuslaser s'il sort de l'écran
    }
}

void BonusLaser::applyEffect(Paddle& paddle,
                             std::vector<std::shared_ptr<BonusLaser>>& lasers,
                             std::vector<std::shared_ptr<Block>>& blocks,
                             std::vector<std::shared_ptr<Capsule>>& capsules,
                             Level& level){

    if (!paddle.isLaserModeEnabled()) {
        return;
    }
    for (auto& laser : lasers) {
        laser->update(1.0 / 60.0);

        for (auto& block : level.get_blocks()){
            if (!block->getVisibility()) continue; // Ignore invisible blocks

                float blockX = block->getPosition().x;
                float blockY = block->getPosition().y;
                float blockWidth = block->getSize().width;
                float blockHeight = block->getSize().height;


                float laserX = laser->getPosition().x;
                float laserY = laser->getPosition().y;
                float laserWidth = 2;   // Assuming laser width is 2 (or adjust if you have a different width)
                float laserHeight = 10;  // Assuming laser height is 10 (or adjust if you have a different height)

                // Check if the laser rectangle intersects the block's rectangle
                if (laserX + laserWidth > blockX && laserX < blockX + blockWidth &&
                    laserY + laserHeight > blockY && laserY < blockY + blockHeight) {
                    if (!block->colors_are_equals(block->getColor(), COLOR_GOLD)) {
                        block->setVisibility(false);

                        if (block->hasCapsule()) {
                            capsules.push_back(block->getCapsule());
                        }
                    }

                    if (block->colors_are_equals(block->getColor(), COLOR_SILVER)) {
                        // TODO : Gérer les blocs SILVER
                    }

                    laser->setInactive();
                    break; // Gérer une seule collision par laser
                }
            }
        }
    }
void Laser::update(float deltaTime) {
    position_.y -= speed_ * deltaTime; // Le laser monte vers le haut
    if (position_.y < 0) {
        active_ = false; // Désactiver le laser s'il sort de l'écran
    }
}
// Dessiner le bonuslaser
void BonusLaser::draw() const {
    if (active_) {
        al_draw_filled_rectangle(position_.x - 2, position_.y, position_.x + 2, position_.y + 10, color_);
    }
}

// Vérifie si le bonuslaser est actif
bool BonusLaser::isActive() const {
    return active_;
}

// Récupérer la position du bonuslaser
const Point& BonusLaser::getPosition() const {
    return position_;
}

// Désactiver le bonuslaser
void BonusLaser::setInactive() {
    active_ = false;
}