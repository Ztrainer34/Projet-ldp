#ifndef PADDLE_HPP
#define PADDLE_HPP


#include "Point.hpp"
#include "Size.hpp"
#include "color.hpp"
#include "Object.hpp"

#include <allegro5/allegro_color.h>
#include <vector>
#include <memory>
#include "Laser.hpp"

// Déclarations anticipées



class Paddle : public Object {
private:
    Point center_;           // Center position of the paddle
    Size size_;              // Size of the paddle
    float speed_;            // Speed of the paddle
    ALLEGRO_COLOR frameColor_;  // Frame color of the paddle
    ALLEGRO_COLOR fillColor_;   // Fill color of the paddle
    bool laser_mode_ = false;

public:
        // Constructor
        Paddle(Point center, float speed, Size size,
            ALLEGRO_COLOR frameColor = COLOR_BLACK, ALLEGRO_COLOR fillColor = COLOR_GREY, bool laser_mode = false);

        void draw() override; // Le mot-clé override indique explicitement que draw() remplace une méthode virtuelle, donc le virtual est redondant ici.

        // handle bonus laser
        void enlarge(float amount) { size_.width += amount;}
        bool isLaserModeEnabled() const;
        void enableLaserMode();
        void shootLaser(std::vector<Laser>& lasers);

    
        // Handle mouse movement for the paddle
        void moveLeft(float delta, float boundary_left);
        void moveRight(float delta, float boundary_right);

};

#endif // PADDLE_HPP