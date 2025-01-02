#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Point.hpp"
#include "Size.hpp"

class Object {
protected:
    Point position_;
    Size size_; 
    Object()                             = default;
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
    virtual Size getSize() const{
        return size_;
    }

    virtual ~Object() = default;
};
#endif // OBJECT_HPP
