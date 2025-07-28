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

    void enlarge(float amount) { setWidth(getWidth() + amount); }
    bool isLaserModeEnabled() const { return laser_mode_; }
    void setLaserMode(bool enabled) { laser_mode_ = enabled; }

};

#endif // PADDLE_HPP