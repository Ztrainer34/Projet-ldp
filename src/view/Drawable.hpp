#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <allegro5/allegro.h>
// Abstract base class for drawable objects
class Drawable {
protected:
    // Default constructor, copy constructor, move constructor, and assignment operators
    ALLEGRO_COLOR frameColor;  
    ALLEGRO_COLOR fillColor; 

    Drawable() = default;
    Drawable(const Drawable &) = default;
    Drawable(Drawable &&) = default;
    Drawable &operator=(const Drawable &) = default;
    Drawable &operator=(Drawable &&) = default;

public:
    // Pure virtual function that must be implemented by derived classes
    virtual void draw() = 0;

    virtual bool colors_are_equals() = 0;

    // Virtual destructor to ensure proper cleanup for derived classes
    virtual ~Drawable() = default;
};

#endif // DRAWABLE_H