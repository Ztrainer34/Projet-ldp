#ifndef BLOCK_H
#define BLOCK_H

#include "Object.hpp"
#include <memory>
#include <vector>
#include "../../utils/Constants.hpp"

namespace C = Constants;
// Déclarations anticipées
class Capsule;

class Block : public Object {
private:          

    //Bonus bonus_;
    bool has_capsule_;
    std::shared_ptr<Capsule> capsule_;
    int hitCount_ = 0;
    bool active = true; 
    char type_;

public:
    Block(Point position, Size size, bool visible, char type);

    void draw() override;

    // Handle collision with a ball
    

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