#ifndef CAPSULE_HPP
#define CAPSULE_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Paddle.hpp"

class Capsule : public Drawable {
public:
    // Constructor
    Capsule(float x, float y, float width, float height, ALLEGRO_COLOR color);

    // Draws the capsule on the screen
    void draw() override;

    // Updates the capsule's position
    void update();

    // Getters
    bool isVisible() const;
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    // Setters
    void setVisible(bool visible);
    bool checkCollision(Paddle& paddle) const;
    bool colors_are_equals(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2);
    ALLEGRO_COLOR getColor() const;


private:
    float x_, y_;               // Position of the capsule
    float width_, height_;      // Dimensions of the capsule
    float speed_ = 0.00005;      // Speed of the capsule
    ALLEGRO_COLOR color_;       // Color of the capsule
    bool visible_;              // Visibility state of the capsule
};

#endif // CAPSULE_HPP
