#include "Laser.hpp"
#include <allegro5/allegro_primitives.h>


// Constructeur
Laser::Laser(float x, float y, float speed, ALLEGRO_COLOR color)
    : position_(x, y), speed_(speed), color_(color), active_(true) {}

// Mise à jour de la position du laser
void Laser::update(float deltaTime) {
    position_.y -= speed_ * deltaTime; // Le laser monte vers le haut
    if (position_.y < 0) {
        active_ = false; // Désactiver le laser s'il sort de l'écran
    }
}

// Dessiner le laser
void Laser::draw() const {
    if (active_) {
        al_draw_filled_rectangle(position_.x - 2, position_.y, position_.x + 2, position_.y + 10, color_);
    }
}

// Vérifie si le laser est actif
bool Laser::isActive() const {
    return active_;
}

// Récupérer la position du laser
const Point& Laser::getPosition() const {
    return position_;
}

// Désactiver le laser
void Laser::setInactive() {
    active_ = false;
}
