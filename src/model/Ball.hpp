/**
 * @file Ball.hpp
 * @brief Déclare la balle: mouvement, split, et mécanisme de capture/lancement.
 */
#ifndef BALL_H
#define BALL_H


#include "Object.hpp"

#include <vector>

// todo methode reset

// Déclarations anticipées
class Paddle;
class Block;

/**
 * @class Ball
 * @brief Balle du jeu: mouvement, split, capture sur raquette, relance.
 */
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
    /** Met à jour la position si la balle n'est pas capturée. */
    void updatePosition() override;

    /** Sépare la balle en trois en modifiant légèrement les directions. */
    std::vector<Ball> split();

    // Ball catch functionality
    /** La balle est-elle actuellement capturée sur la raquette ? */
    bool isCaught() const { return isCaught_; }
    /** Définit l'état capturé/de-capturé. */
    void setCaught(bool caught) { isCaught_ = caught; }
    /** Positionne la balle et l'arme en mode "capturé" lorsque la raquette l'attrape. */
    void catchBall(const Paddle& paddle);
    /** Relâche la balle avec une vitesse initiale ascendante. */
    void launchBall();
    /** Maintient la balle capturée centrée sur la raquette. */
    void updateCaughtPosition(const Paddle& paddle);

    // Getter and Setter for radius
    float getRadius() const;
    void setRadius(float new_radius);

    bool IsBallMissed() const ;
    // Draw the ball
    void resetBallPosition();
    
};

#endif // BALL_H