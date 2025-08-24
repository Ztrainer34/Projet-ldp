/**
 * @file Paddle.cpp
 * @brief Implémentation de la raquette (construction et dépendances).
 */
#include "Paddle.hpp"
#include <allegro5/allegro_primitives.h>
#include "algorithm"

#include "Laser.hpp"



Paddle::Paddle(Point position, Size size, Speed speed,  bool laser_mode) : 
    Object(position, size, speed), laser_mode_(laser_mode) {}



