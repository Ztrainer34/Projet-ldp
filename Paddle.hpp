#ifndef PADDLE_H
#define PADDLE_H

#include "Drawable.h"
#include "Point.h"
#include "Size.h"
#include  "color.h"
#include  "Laser.hpp"
#include  <vector>
#include <allegro5/allegro_color.h>

// Define colors

class Paddle : public virtual Drawable {
private:
    Point center_;           // Center position of the paddle
    Size size_;              // Size of the paddle
    float speed_;            // Speed of the paddle
    ALLEGRO_COLOR frameColor_;  // Frame color of the paddle
    ALLEGRO_COLOR fillColor_;   // Fill color of the paddle

    bool laser_mode_ = false;

public:
    // Constructor
    Paddle(float x, float y, float speed, float width, float height,
           ALLEGRO_COLOR frameColor = COLOR_BLACK, ALLEGRO_COLOR fillColor = COLOR_GREY);

    // Draw the paddle
    void draw() override;

    // Update position of the paddle
    void update_position(Point &new_position);

    // Handle collisions (Placeholder logic)
    void collision();

    // Get the current position of the paddle
    Point get_position();
    Size get_size();
    // Handle mouse movement for the paddle
    void move_left(float delta, float boundary_left);
    void move_right(float delta, float boundary_right);
    void enlarge(float amount) { size_.width += amount;}
    bool isLaserModeEnabled() const;
    void enableLaserMode();
    void shootLaser(std::vector<Laser>& lasers);
};



#endif // PADDLE_H
