#ifndef SIZE_H
#define SIZE_H

struct Size {
    float width;
    float height;
    Size() : width(0), height(0) {} // Constructeur par défaut pour éviter les erreurs
    Size(float width_, float height_) : width(width_), height(height_) {}
};

#endif