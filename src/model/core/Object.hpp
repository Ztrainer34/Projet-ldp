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
    Object() : position_(), size_(), speed_() {}
    Object(Point position, Size size, Speed speed) 
        : position_(position), size_(size), speed_(speed) {}

    Object(const Object &)            = default;
    Object(Object &&)                 = default;
    Object &operator=(const Object &) = default;
    Object &operator=(Object &&)      = default;

public:
    virtual void draw() = 0;
    
    virtual Point getPosition() const {
        return position_;
    }
    virtual void  setPosition(const Point &newPosition){
        position_ = newPosition;
    }

    void setPosition(float x, float y) noexcept { position_.setPosition(x, y); }
    
    virtual Size getSize() const { return size_; }

    virtual void setSize(const Size& newSize) { size_ = newSize; }

    virtual Speed getSpeed() const { return speed_; }

    virtual void setSpeed(const Speed& newSpeed) { speed_ = newSpeed; }

    virtual void updatePosition() = 0;

    virtual void updatePosition(float delta) {}

    virtual ~Object() = default;
};
#endif // OBJECT_HPP