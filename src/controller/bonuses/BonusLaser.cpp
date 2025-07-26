#include "BonusLaser.hpp"
#include <allegro5/allegro_primitives.h>
#include "../../model/Block.hpp"
#include "../../model/Capsule.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/game/Level.hpp"

// Constructeur
BonusLaser::BonusLaser(float x, float y, float speed, ALLEGRO_COLOR color)
    : Bonus(Point(x, y),'L', color), position_(x, y), speed_(speed), color_(color), active_(true) {}

// Mise à jour de la position du bonuslaser
void BonusLaser::update(float deltaTime) {
    //position_.y -= speed_ * deltaTime; // Le bonuslaser monte vers le haut
    position_.setY(position_.getY() - speed_ * deltaTime);
    if (position_.getY() < 0) {
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
            if (!block->isVisible()) continue; // Ignore invisible blocks

                float blockX = block->getPosition().getX();
                float blockY = block->getPosition().getY();
                float blockWidth = block->getSize().getWidth();
                float blockHeight = block->getSize().getHeight();


                float laserX = laser->getPosition().getX();
                float laserY = laser->getPosition().getY();
                float laserWidth = 2;   // Assuming laser width is 2 (or adjust if you have a different width)
                float laserHeight = 10;  // Assuming laser height is 10 (or adjust if you have a different height)

                // Check if the laser rectangle intersects the block's rectangle
                if (laserX + laserWidth > blockX && laserX < blockX + blockWidth &&
                    laserY + laserHeight > blockY && laserY < blockY + blockHeight) {
                    if (!colorsAreEqual(block->getColor(), COLOR_GOLD)) {
                        block->setVisibility(false);

                        if (block->hasCapsule()) {
                            capsules.push_back(block->getCapsule());
                        }
                    }

                    if (!colorsAreEqual(block->getColor(), COLOR_GOLD)) {
                        // TODO : Gérer les blocs SILVER
                    }

                    laser->setInactive();
                    break; // Gérer une seule collision par laser
                }
            }
        }
    }

// Dessiner le bonuslaser
void BonusLaser::draw() const {
    if (active_) {
        al_draw_filled_rectangle(position_.getX() - 2, position_.getY(), position_.getX() + 2, position_.getY() + 10, color_);
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