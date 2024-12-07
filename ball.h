#ifndef BALL_H
#define BALL_H

#include "Drawable.h"
#include "Point.h"
#include <allegro5/allegro_color.h>

class Ball : public virtual Drawable {
private:
    Point position;           // Position of the ball
    float speed;              // Speed of the ball
    float radius;             // Radius of the ball
    ALLEGRO_COLOR frameColor; // Color of the ball's border
    ALLEGRO_COLOR fillColor;  // Color of the ball's fill

public:
    // Constructor
    Ball(float x, float y, float speed, float radius,
         ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor);

    // Update the ball's position
    void update_position();

    // Handle collisions (to be implemented)
    void collision();

    // Getters and Setters for position
    Point getPosition() const;
    void setPosition(const Point& new_position);

    // Getter and Setter for radius
    float getRadius() const;
    void setRadius(float new_radius);

    // Draw the ball
    void draw() override;
};

#endif // BALL_H
