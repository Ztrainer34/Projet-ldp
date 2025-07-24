#ifndef BLOCK_H
#define BLOCK_H

#include "Object.hpp"
#include <memory>
#include <vector>
#include <allegro5/allegro.h>  // Pour ALLEGRO_COLOR et al_map_rgb()

namespace C = Constants;
// Déclarations anticipées
class Capsule;

class Block : public Object {
protected:          

    //Bonus bonus_;
    bool has_capsule_;
    std::shared_ptr<Capsule> capsule_;
    int hitPoints_;
    unsigned int scoreValue_;
    ALLEGRO_COLOR color_;
    bool active = true; 

public:
    Block(Point position, Size size, bool visible, ALLEGRO_COLOR color, int hitPoints, int score);
    Block(Point position, Size size, bool visible, int hitPoints);
    // Handle collision with a ball
    
    int getHp() const { return hitPoints_; } // Get the current hit count
    void incrementHits() { hitPoints_++; }    // Increment the hit coun
    virtual void onHit() { hitPoints_--;
                            if(hitPoints_ <= 0) setVisibility(false);  }


    unsigned int getScoreValue() const { return scoreValue_; }

    ALLEGRO_COLOR getColor() const { return color_; }

    void setbonus(bool bonus);
    bool getbonus() const;

    void setCapsule(std::shared_ptr<Capsule> capsule);
    std::shared_ptr<Capsule> getCapsule() const ;
    bool hasCapsule() const;
    void destroy(std::vector<std::shared_ptr<Capsule>>& capsules);
    
    virtual ~Block() = default;
};

#endif // BLOCK_H