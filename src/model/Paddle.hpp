/**
 * @file Paddle.hpp
 * @brief Déclare la raquette du joueur (mode laser, agrandissement).
 */
#ifndef PADDLE_HPP
#define PADDLE_HPP


#include "Object.hpp"

#include <vector>
#include <memory>
#include "Laser.hpp"

// Déclarations anticipées



class Paddle : public Object {
private:
    bool laser_mode_ = false;

public:
    // Constructor
    Paddle(Point position, Size size, Speed speed, bool laser_mode);

    /** Agrandit la largeur de la raquette de amount. */
    void enlarge(float amount) { setWidth(getWidth() + amount); }
    /** Mode laser activé ? */
    bool isLaserModeEnabled() const { return laser_mode_; }
    /** Active/désactive le mode laser. */
    void setLaserMode(bool enabled) { laser_mode_ = enabled; }

};

#endif // PADDLE_HPP