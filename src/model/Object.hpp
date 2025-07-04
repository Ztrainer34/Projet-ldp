#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Point.hpp"
#include "Size.hpp"
#include "Speed.hpp"
#include "../utils/Constants.hpp"

namespace CST = Constants;
class Object {
protected:
    Point position_;
    Size size_; 
    Speed speed_;
    bool visible_;
    

public:
    Object() : position_(), size_(), speed_(), visible_() {}
    Object(Point position, Size size, Speed speed) 
        : position_(position), size_(size), speed_(speed) {}
    
    Object(Point position, Speed speed) : position_(position), speed_(speed) {}
    Object(Point position, Size size, bool visible) : position_(position), size_(size), visible_(visible) {}

    Object(const Object &)            = default;
    Object(Object &&)                 = default;
    Object &operator=(const Object &) = default;
    Object &operator=(Object &&)      = default;
    
     float getX() const { return position_.getX(); }
     float getY() const { return position_.getY(); }

     Point getPosition() const {
        return position_;
    }
     void  setPosition(const Point &newPosition){
        position_ = newPosition;
    }
    void setPosition(float x, float y) noexcept { position_.setPosition(x, y); }
    void setX(float x) { return position_.setX(x); }
    void setY(float y) { return position_.setY(y); }
    
    Size getSize() const { return size_; }
    void setSize(const Size& newSize) { size_ = newSize; }
    float getWidth() const { return size_.getWidth(); }
    float getHeight() const { return size_.getHeight(); }
    void setWidth(float newWidth) { size_.setWidth(newWidth); }
    void setHeight(float newHeight) { size_.setHeight(newHeight); }

    Speed getSpeed() const { return speed_; }
    float getSpeedX() const { return speed_.getSpeedX(); }
    float getSpeedY() const { return speed_.getSpeedY(); }
    void setSpeed(const Speed& newSpeed) { speed_ = newSpeed; }
    void setSpeed(float x, float y) { speed_.setSpeed(x, y); }
    void setSpeedX(float x) { speed_.setSpeedX(x); }
    void setSpeedY(float y) { speed_.setSpeedY(y); }

    virtual void updatePosition() { }

    virtual void updatePosition(float delta) { } 

    bool isVisible() const { return visible_; };
    void setVisibility(bool newVisible) { visible_ = newVisible; }

    virtual ~Object() = default;

};
#endif // OBJECT_HPP