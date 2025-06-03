#ifndef LASER_HPP
#define LASER_HPP

#include <allegro5/allegro.h>
#include "Point.hpp"


class Laser : public Object {
private:
    Point position_;
    float speed_;
    ALLEGRO_COLOR color_;
    bool active_;
    
public:
    // Constructeur
    Laser(float x, float y, float speed, ALLEGRO_COLOR color);

    // Mise à jour de la position du laser
    void update(float deltaTime);

    // Dessiner le laser
    void draw() const;

    // Vérifie si le laser est actif
    bool isActive() const;

    // Désactiver le laser
    void setInactive();

};

#endif // LASER_HPP
