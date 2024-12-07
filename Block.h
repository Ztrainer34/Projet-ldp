#ifndef BLOCK_H
#define BLOCK_H

#include "Drawable.h"
#include "Point.h"
#include "Size.h"
#include <allegro5/allegro5.h>

class Block : public Drawable {
    Point position_block;
    Size size_block;
    bool is_visible;
    ALLEGRO_COLOR frameColor;
    ALLEGRO_COLOR fillColor;

public:
    Block(float x, float y, float width, float height, ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor);

    void draw() override;

    // Handle collision with a ball

    // Getters and Setters for position_block
    Point getPosition() const;
    void setPosition(float x, float y);
    void setPosition(const Point& new_position);

    // Additional methods to access visibility and size
    bool getVisibility() const;
    void setVisibility(bool visibility);
    Size getSize() const;
};

#endif // BLOCK_H
