#ifndef BLOCK_H
#define BLOCK_H


#include "Point.hpp"
#include "Size.hpp"
#include <allegro5/allegro5.h>
#include "color.hpp"
#include "Object.hpp"
#include <memory>

#include <vector>

// Déclarations anticipées
class Capsule;

class Block : public Object {
private:          
    bool isVisible;            // Visibilité du bloc 

    //Bonus bonus_;
    bool has_capsule_;
    std::shared_ptr<Capsule> capsule_;
    int hitCount_ = 0;
    bool active = true; 
    char type_;

public:
    Block(Point position, Size size, char type);

    void draw() override;

    // Handle collision with a ball

    // Getters and Setters 
    Point getPosition() const;
    void setPosition(float x, float y);
    void setPosition(const Point& new_position);
    ALLEGRO_COLOR getFrameColor() const;
    Size getSize() const;
    // Additional methods to access visibility and size
    bool getVisibility() const;
    void setVisibility(bool visibility);
    void setFrameColor(ALLEGRO_COLOR& new_color);
    ALLEGRO_COLOR getColor() const;

    int getHits() const { return hitCount_; } // Get the current hit count
    void incrementHits() { hitCount_++; }    // Increment the hit coun

    void setbonus(bool bonus);
    bool getbonus() const;
    void setCapsule(std::shared_ptr<Capsule> capsule);
    std::shared_ptr<Capsule> getCapsule() const ;
    bool hasCapsule() const;
    void destroy(std::vector<std::shared_ptr<Capsule>>& capsules);
    bool colors_are_equals(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2);
};

#endif // BLOCK_H