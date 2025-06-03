#pragma once

class Speed {
private:
    float speedX;
    float speedY;

public:
    Speed() : speedX(0), speedY(0) {}
    Speed(float speedX_, float speedY_) : speedX(speedX_), speedY(speedY_) {}

    // Getters (accesseurs)
    float getSpeedX() const { return speedX; }
    float getSpeedY() const { return speedY; }
    
    // Setters (mutateurs)
    void setSpeedX(float newSpeedX) { speedX = newSpeedX; }
    void setSpeedY(float newSpeedY) { speedY = newSpeedY; }
    void setSpeed(float newSpeedX, float newSpeedY) { // Pour modifier les deux en une opération
        speedX = newSpeedX;
        speedY = newSpeedY;
    }

    // Opérateurs utiles
    Speed operator+(const Speed& other) const {
        return Speed(speedX + other.speedX, speedY + other.speedY);
    }

    Speed& operator+=(const Speed& other) {
        speedX += other.speedX;
        speedY += other.speedY;
        return *this;
    }

};