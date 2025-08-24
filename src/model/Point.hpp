/**
 * @file Point.hpp
 * @brief Représente un point 2D avec coordonnées flottantes et utilitaires.
 */
#ifndef POINT_H
#define POINT_H

class Point {
private:
    float x;
    float y;

public:
    Point() : x(0), y(0) {} // Constructeur par défaut pour éviter les erreurs
    Point(float x_, float y_) : x(x_), y(y_) {}

    float getX() const { return x; }
    float getY() const { return y; }

    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY;}

    /** Définit d'un coup les deux coordonnées. */
    void setPosition(float newX, float newY){
        x = newX;
        y = newY;
    }

    /** Additionne deux points composante par composante. */
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    /** Addition-assignation composante par composante. */
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

};

#endif // POINT_H