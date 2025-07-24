#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>                // Core Allegro functions
#include <allegro5/allegro_font.h>           // Font rendering
#include <allegro5/allegro_primitives.h>     // Drawing shapes
#include <allegro5/allegro_ttf.h>
#include <cmath>
// Abstract base class for drawable objects
class Drawable {
protected:
    // Default constructor, copy constructor, move constructor, and assignment operators
    ALLEGRO_COLOR frameColor;  
    ALLEGRO_COLOR fillColor; 

    
    Drawable(ALLEGRO_COLOR frame, ALLEGRO_COLOR fill)
        : frameColor(frame), fillColor(fill) {}


    Drawable(const Drawable &) = default;
    Drawable(Drawable &&) = default;
    Drawable &operator=(const Drawable &) = default;
    Drawable &operator=(Drawable &&) = default;

public:
    // Pure virtual function that must be implemented by derived classes
    virtual void draw() = 0;

    ALLEGRO_COLOR getFrameColor() const { return frameColor; }
    ALLEGRO_COLOR getFillColor() const { return fillColor; }

    //virtual bool colorsAreEqual() = 0;
    //virtual bool colorsAreEqual(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2) = 0;

    bool colorsAreEqual(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2) const {
        constexpr float COLOR_EPSILON = 0.001f;
        return (std::fabs(c1.r - c2.r) < COLOR_EPSILON &&
                std::fabs(c1.g - c2.g) < COLOR_EPSILON &&
                std::fabs(c1.b - c2.b) < COLOR_EPSILON &&
                std::fabs(c1.a - c2.a) < COLOR_EPSILON);
    }

    void setFrameColor(const ALLEGRO_COLOR& new_color) { frameColor = new_color; }
    void setFillColor(const ALLEGRO_COLOR& new_color) { fillColor = new_color; }

    // Virtual destructor to ensure proper cleanup for derived classes
    virtual ~Drawable() = default;
};

#endif // DRAWABLE_H