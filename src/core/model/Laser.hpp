#ifndef LASER_HPP
#define LASER_HPP

#include <allegro5/allegro.h>
#include "Object.hpp"


class Laser : public Object {
private:

    bool active_;
    
public:
    Laser(Point position, Speed speed);

    // Mise à jour de la position du laser
    void updatePosition(float deltaTime) override;

    

    // Vérifie si le laser est actif
    bool isActive() const;

    // Désactiver le laser
    void setInactive();

};

#endif // LASER_HPP
