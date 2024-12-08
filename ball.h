#ifndef BALL_H
#define BALL_H

#include "Drawable.h"
#include "Point.h"
#include <allegro5/allegro_color.h>
#include "paddle.h"
#include "Block.h"
struct speed {
    float speed_x;
    float speed_y;
};


class Ball : public virtual Drawable {
private:
    Point position;           // Position of the ball
    speed speed_;            // Speed of the ball
    float radius;             // Radius of the ball
    ALLEGRO_COLOR frameColor; // Color of the ball's border
    ALLEGRO_COLOR fillColor;  // Color of the ball's fill

public:
    // Constructor
    Ball(float x, float y, float speed_x, float speed_y, float radius,
         ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor);

    // Update the ball's position
    void update_position();

    // Handle collisions (to be implemented)
    void handle_paddle_collision(float paddleX, float paddleWidth);
    bool is_touching(Paddle& paddle) const;
    // Getters and Setters for position
    Point getPosition() const;
    void setPosition(const Point& new_position);
    void handle_screen_collision(float screen_width, float screen_height);
    bool is_touching_screen_boundary(float screen_width, float screen_height) const;
    void handle_brick_collision(Block& brick);
    bool is_touching_brick(const Block& brick) const ;
    // Getter and Setter for radius
    float getRadius() const;
    void setRadius(float new_radius);
    speed getspeed() const;


    // Draw the ball
    void draw() override;
};

#endif // BALL_H
