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
    bool isCaught_;           // Flag to track if ball is caught by paddle

public:
    // Constructor
    Ball(Point position, float radius);
    Ball(Point position, Speed speed, float radius);
        

    //Ball(float x, float y, float speed_x, float speed_y, float radius);

    // Update the ball's position
    void updatePosition() override;

    std::vector<Ball> split();

    // Ball catch functionality
    bool isCaught() const { return isCaught_; }
    void setCaught(bool caught) { isCaught_ = caught; }
    void catchBall(const Paddle& paddle);
    void launchBall();
    void updateCaughtPosition(const Paddle& paddle);

    // Getter and Setter for radius
    float getRadius() const;
    void setRadius(float new_radius);

    bool IsBallMissed() const ;
    // Draw the ball
    void resetBallPosition();
    
};

#endif // BALL_H