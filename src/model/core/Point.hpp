#ifndef POINT_H
#define POINT_H

struct Point {
    float x;
    float y;
    Point() : x(0), y(0) {} // Constructeur par défaut pour éviter les erreurs
    Point(float x_, float y_) : x(x_), y(y_) {}
};

#endif // POINT_H