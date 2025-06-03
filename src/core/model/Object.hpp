#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Point.hpp"
#include "Size.hpp"
#include "Speed.hpp"

class Object {
protected:
    Point position_;
    Size size_; 
    Speed speed_;
    virtual ~Object() = default;

public:
    Object() : position_(), size_(), speed_() {}
    Object(Point position, Size size, Speed speed) 
        : position_(position), size_(size), speed_(speed) {}
    
    Object(Point position, Speed speed) : position_(position), speed_(speed) {}
    Object(Point position, Size size) : position_(position), size_(size) {}

    Object(const Object &)            = default;
    Object(Object &&)                 = default;
    Object &operator=(const Object &) = default;
    Object &operator=(Object &&)      = default;

    virtual void draw() = 0;
    
    virtual float getX() const { return position_.getX(); }
    virtual float getY() const { return position_.getY(); }

    virtual Point getPosition() const {
        return position_;
    }
    virtual void  setPosition(const Point &newPosition){
        position_ = newPosition;
    }
    void setPosition(float x, float y) noexcept { position_.setPosition(x, y); }
    void setX(float x) { return position_.setX(x); }
    void setY(float y) { return position_.setY(y); }
    
    virtual Size getSize() const { return size_; }
    virtual void setSize(const Size& newSize) { size_ = newSize; }
    virtual float getWidth() const { return size_.getWidth(); }
    virtual float getHeight() const { return size_.getHeight(); }
    virtual void setWidth(float newWidth) { size_.setWidth(newWidth); }
    virtual void setHeight(float newHeight) { size_.setHeight(newHeight); }

    virtual Speed getSpeed() const { return speed_; }
    virtual float getSpeedX() const { return speed_.getSpeedX(); }
    virtual float getSpeedY() const { return speed_.getSpeedY(); }
    virtual void setSpeed(const Speed& newSpeed) { speed_ = newSpeed; }
    virtual void setSpeed(float x, float y) { speed_.setSpeed(x, y); }
    virtual void setSpeedX(float x) { speed_.setSpeedX(x); }
    virtual void setSpeedY(float y) { speed_.setSpeedY(y); }

    virtual void updatePosition() = 0;

    virtual void updatePosition(float delta) {}

    virtual void isVisible() = 0;

};
#endif // OBJECT_HPP