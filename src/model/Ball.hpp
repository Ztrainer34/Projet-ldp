#ifndef BALL_H
#define BALL_H


#include "Object.hpp"

#include <vector>

// todo methode reset

// Déclarations anticipées
class Paddle;
class Block;

class Ball : public Object {
private:
    float radius_;             // Radius of the ball

public:
    // Constructor
    Ball(Point position, float radius);
    Ball(Point position, Speed speed, float radius);
        

    //Ball(float x, float y, float speed_x, float speed_y, float radius);

    // Update the ball's position
    void updatePosition() override;

    std::vector<Ball> split();


    // Getter and Setter for radius
    float getRadius() const;
    void setRadius(float new_radius);

    bool IsBallMissed() const ;
    // Draw the ball
    
};

#endif // BALL_H