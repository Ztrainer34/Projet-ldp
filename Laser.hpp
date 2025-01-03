#ifndef LASER_HPP
#define LASER_HPP

#include <allegro5/allegro.h>
#include "Point.h"





class Laser {
public:
    // Constructeur
    Laser(float x, float y, float speed, ALLEGRO_COLOR color);

    // Mise à jour de la position du laser
    void update(float deltaTime);

    // Dessiner le laser
    void draw() const;

    // Vérifie si le laser est actif
    bool isActive() const;

    // Récupère la position du laser
    const Point& getPosition() const;

    // Désactiver le laser
    void setInactive();


private:
    Point position_;
    float speed_;
    ALLEGRO_COLOR color_;
    bool active_;
};

#endif // LASER_HPP
