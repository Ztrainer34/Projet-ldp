/**
 * @file Laser.cpp
 * @brief Implémentation du projectile laser.
 */
#include "Laser.hpp"
#include <allegro5/allegro_primitives.h>


Laser::Laser(Point position, Speed speed) : 
    Object(position, speed), active_(true) {}

// Mise à jour de la position du laser
/**
 * @brief Déplace le laser vers le haut et le désactive s'il sort de l'écran.
 */
void Laser::updatePosition(float delta) {
    // Calcul du déplacement vertical
    float newY = getY() + getSpeedY() * delta;
    setY(newY);

    // Vérifie si le laser est encore visible
    if (newY < 0) {
        setInactive();
    }
}


// Vérifie si le laser est actif
bool Laser::isActive() const {
    return active_;
}

// Désactiver le laser
void Laser::setInactive() {
    active_ = false;
}
