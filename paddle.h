#ifndef PADDLE_H
#define PADDLE_H

#include "Drawable.h"
#include "Point.h"
#include "Size.h"
#include <allegro5/allegro_color.h>

// Define colors
#define COLOR_BLACK al_map_rgb(0, 0, 0)
#define COLOR_GREY  al_map_rgb(128, 128, 128)

class Paddle : public virtual Drawable {
private:
    Point center_;           // Center position of the paddle
    Size size_;              // Size of the paddle
    float speed_;            // Speed of the paddle
    ALLEGRO_COLOR frameColor_;  // Frame color of the paddle
    ALLEGRO_COLOR fillColor_;   // Fill color of the paddle

public:
    // Constructor
    Paddle(float x, float y, float speed, float width, float height,
           ALLEGRO_COLOR frameColor = COLOR_BLACK, ALLEGRO_COLOR fillColor = COLOR_GREY);

    // Draw the paddle
    void draw() override;

    // Update position of the paddle
    void update_position();

    // Handle collisions (Placeholder logic)
    void collision();

    // Get the current position of the paddle
    Point get_position();

    // Handle mouse movement for the paddle
    void mouseMove(Point mouseLoc);
};

#endif // PADDLE_H
