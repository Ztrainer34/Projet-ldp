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

        // Comportement “pur” sans input spécifique
        void enlarge(float amount) { setWidth(amount); }

};

#endif // PADDLE_HPP