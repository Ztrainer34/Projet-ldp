/**
 * @file Laser.hpp
 * @brief Déclare le projectile laser tiré par la raquette.
 */
#ifndef LASER_HPP
#define LASER_HPP

#include <allegro5/allegro.h>
#include "Object.hpp"


class Laser : public Object {
private:

    bool active_;
    
public:
    /** Construit un laser à une position et vitesse données. */
    Laser(Point position, Speed speed);

    // Mise à jour de la position du laser
    /** Met à jour la position verticale du laser (delta en secondes). */
    void updatePosition(float deltaTime) override;

    // Vérifie si le laser est actif
    /** Indique si le laser est encore actif (visible/utilisable). */
    bool isActive() const;

    // Désactiver le laser
    /** Marque le laser comme inactif. */
    void setInactive();

};

#endif // LASER_HPP
