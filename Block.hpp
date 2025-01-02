#ifndef BLOCK_H
#define BLOCK_H

#include "Drawable.h"
#include "Point.h"
#include "Size.h"
#include <allegro5/allegro5.h>
#include "Bonus.hpp"
#include <memory>
#include "Capsule.h"
#include <vector>

class Block : public Drawable {
    Point position_block;
    Size size_block;
    bool is_visible;
    ALLEGRO_COLOR frameColor;
    ALLEGRO_COLOR fillColor;

    Bonus bonus_;
    bool has_capsule_;
    std::shared_ptr<Capsule> capsule_;
    int hitCount_ = 0;
    bool ative = true;

public:
    Block(float x, float y, float width, float height, ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor,char type);

    void draw() override;

    // Handle collision with a ball


    // Getters and Setters for position_block
    Point getPosition() const;
    void setPosition(float x, float y);
    void setPosition(const Point& new_position);
    ALLEGRO_COLOR getFrameColor() const;
    // Additional methods to access visibility and size
    bool getVisibility() const;
    void setVisibility(bool visibility);
    Size getSize() const;
    ALLEGRO_COLOR getColor() const;
    void setFrameColor(ALLEGRO_COLOR& new_color);
    int getHits() const { return hitCount_; } // Get the current hit count
    void incrementHits() { hitCount_++; }    // Increment the hit coun

    void setbonus(bool bonus);
    bool getbonus() const;
    void setCapsule(std::shared_ptr<Capsule> capsule);
    std::shared_ptr<Capsule> getCapsule() const ;
    bool hasCapsule() const;
    void destroy(std::vector<std::shared_ptr<Capsule>>& capsules);
};

#endif // BLOCK_H
