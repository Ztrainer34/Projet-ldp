/**
 * @file BonusLaser.cpp
 * @brief Implémentation du bonus de tir laser.
 */
#include "BonusLaser.hpp"
#include <allegro5/allegro_primitives.h>
#include "../../model/Block.hpp"
#include "../../model/Capsule.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/game/Level.hpp"
#include "../GameContext.hpp"
#include <iostream>

// Constructeur
BonusLaser::BonusLaser(float x, float y, float speed, ALLEGRO_COLOR color)
    : Bonus(Point(x, y),'L', color), position_(x, y), speed_(speed), color_(color), active_(true) {}

BonusLaser::BonusLaser() : Bonus() { }

/**
 * @brief Met à jour la position verticale du laser et le désactive si hors écran.
 */
// Mise à jour de la position du bonuslaser
void BonusLaser::update(float deltaTime) {
    //position_.y -= speed_ * deltaTime; // Le bonuslaser monte vers le haut
    position_.setY(position_.getY() - speed_ * deltaTime);
    if (position_.getY() < 0) {
        active_ = false; // Désactiver le bonuslaser s'il sort de l'écran
    }
}

/**
 * @brief Active le mode laser sur la raquette.
 */
void BonusLaser::applyEffect(GameContext& gameContext){
    std::cout << "[DEBUG] BonusLaser applied! Laser mode enabled." << std::endl;
    activate();
    gameContext.paddle.setLaserMode(true); 
}

/**
 * @brief Désactive le mode laser sur la raquette.
 */
void BonusLaser::cancelEffect(GameContext& context){
    deactivate();
    context.paddle.setLaserMode(false);
}

/**
 * @brief Accesseur vers la position courante du bonus laser.
 */
// Récupérer la position du bonuslaser
const Point& BonusLaser::getPosition() const {
    return position_;
}

