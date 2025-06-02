#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <allegro5/allegro.h>
// Abstract base class for renderable objects
class Renderable {
protected:
    // Default constructor, copy constructor, move constructor, and assignment operators
    ALLEGRO_COLOR frameColor;  
    ALLEGRO_COLOR fillColor; 

    Renderable() = default;
    Renderable(const Renderable &) = default;
    Renderable(Renderable &&) = default;
    Renderable &operator=(const Renderable &) = default;
    Renderable &operator=(Renderable &&) = default;

public:
    // Pure virtual function that must be implemented by derived classes
    virtual void draw() = 0;

    // Virtual destructor to ensure proper cleanup for derived classes
    virtual ~Renderable() = default;
};

#endif // RENDERABLE_H