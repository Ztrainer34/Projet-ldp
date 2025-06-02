#ifndef BALL_H
#define BALL_H

#include "Point.hpp"
#include "Object.hpp"

#include <allegro5/allegro_color.h>
#include <vector>

// Déclarations anticipées
class Paddle;
class Block;

class Ball : public Object {
private:
    float radius_;             // Radius of the ball

public:
    // Constructor
    Ball(Point position, float radius);
        

    Ball(float x, float y, float speed_x, float speed_y, float radius);

    // Update the ball's position
    void updatePosition() override;

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

    bool IsBallMissed() const ;
    // Draw the ball
    void draw() override;
};

#endif // BALL_H