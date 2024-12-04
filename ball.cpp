#include <allegro5/allegro5.h>
#include <allegro5/color.h>
#include "Point.h"

class Ball : public virtual Drawable  {
    Point position;
    const ALLEGRO_COLOR COLOR_RED = al_map_rgb(255, 0, 0);
    int speed;
    float radius;

public:
    Ball(float x, float y, int speed, float radius)
        : position{x, y}, speed(speed), radius(radius) {}

    // Update the ball's position
    void update_position() {
        // Logic to update position based on speed or other parameters
    }

    // Handle collisions
    void collision() {
        // Logic to handle collisions
    }

    // Getters and Setters for position
    Point getPosition() const {
        return position;
    }

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void setPosition(const Point& new_position) {
        position = new_position;
    }

    // Getter and Setter for radius
    float getRadius() const {
        return radius;
    }
};

