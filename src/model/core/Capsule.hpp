#ifndef CAPSULE_HPP
#define CAPSULE_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "Point.hpp"
#include "Size.hpp"
#include "Object.hpp"

// Déclarations anticipées
class Paddle;
class Bonus;


class Capsule : public Object {
private:
    float x_, y_;               // Position of the capsule
    Point position_;
    Size size_;
    float width_, height_;      // Dimensions of the capsule
    float speed_ = 0.00005;      // Speed of the capsule
    ALLEGRO_COLOR color_;       // Color of the capsule
    bool visible_;              // Visibility state of the capsule
    std::shared_ptr<Bonus> bonus_; // Composition : Capsule contient un Bonus
public:
    // Constructor
    Capsule(float x, float y, float width, float height, ALLEGRO_COLOR color, std::shared_ptr<Bonus> bonus);
    Capsule(Point position, Size size, ALLEGRO_COLOR color, std::shared_ptr<Bonus> bonus);
    // Nouveau constructeur sans bonus
    Capsule(Point position, Size size, ALLEGRO_COLOR color);


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
    std::shared_ptr<Bonus> getBonus() const;

    // Setters
    void setVisible(bool visible);
    bool checkCollision(Paddle& paddle) const;
    bool colors_are_equals(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2);
    ALLEGRO_COLOR getColor() const;



};

#endif // CAPSULE_HPP