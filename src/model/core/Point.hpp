#ifndef POINT_H
#define POINT_H

class Point {
private:
    float x;
    float y;

public:
    Point() : x(0), y(0) {} // Constructeur par défaut pour éviter les erreurs
    Point(float x_, float y_) : x(x_), y(y_) {}

    float x() const { return x; }
    float y() const { return y; }

    void setPosition(float newX, float newY){
        x = newX;
        y = newY;
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }



};

#endif // POINT_H