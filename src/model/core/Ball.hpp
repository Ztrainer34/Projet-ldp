#ifndef BALL_H
#define BALL_H

#include "Point.hpp"
#include "Object.hpp"
#include <allegro5/allegro_color.h>
#include <vector>

// Déclarations anticipées
class Paddle;
class Block;

struct Speed {
    float speed_x;
    float speed_y;
    Speed(float speed_x_, float speed_y_) : speed_x(speed_x_), speed_y(speed_y_) {}

};


class Ball : public Object {
private:
    Point position_;           // Position of the ball
    Speed speed_;            // Speed of the ball
    float radius_;             // Radius of the ball
    ALLEGRO_COLOR frameColor_; // Color of the ball's border
    ALLEGRO_COLOR fillColor_;  // Color of the ball's fill

public:
    // Constructor
    Ball(Point position, Speed speed, float radius,
         ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor);

    Ball(float x, float y, float speed_x, float speed_y, float radius,
         ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor);

    // Update the ball's position
    void updatePosition();

    std::vector<Ball> split();

    // Handle collisions (to be implemented)
    void handlePaddleCollision(float paddleX, float paddleWidth);
    void handleBrickCollision(Block& brick);
    void handleScreenCollision(float screen_width, float screen_height);

    bool isTouching(Paddle& paddle) const;
    bool isTouchingBrick(const Block& brick) const ;
    bool isTouchingScreenBoundary(float screen_width, float screen_height) const;

    // Getters and Setters for position in class Object
    

    // Getter and Setter for radius
    float getRadius() const;
    void setRadius(float new_radius);
    Speed getspeed() const;
    void setSpeed(Speed newSpeed);

    bool IsBallMissed() const ;
    // Draw the ball
    void draw() override;
};

#endif // BALL_H