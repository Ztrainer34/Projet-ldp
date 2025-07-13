#ifndef BLOCK_H
#define BLOCK_H

#include "Object.hpp"
#include <memory>
#include <vector>


namespace C = Constants;
// Déclarations anticipées
class Capsule;

class Block : public Object {
protected:          

    //Bonus bonus_;
    bool has_capsule_;
    std::shared_ptr<Capsule> capsule_;
    int hitPoints_;
    bool active = true; 

public:
    Block(Point position, Size size, bool visible, int hitPoints);
    // Handle collision with a ball
    
    int getHp() const { return hitPoints_; } // Get the current hit count
    void incrementHits() { hitPoints_++; }    // Increment the hit coun
    virtual void onHit() { hitPoints_--; }

    void setbonus(bool bonus);
    bool getbonus() const;
    void setCapsule(std::shared_ptr<Capsule> capsule);
    std::shared_ptr<Capsule> getCapsule() const ;
    bool hasCapsule() const;
    void destroy(std::vector<std::shared_ptr<Capsule>>& capsules);
    
};

#endif // BLOCK_H