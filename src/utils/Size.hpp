#ifndef SIZE_H
#define SIZE_H

class Size {
private:
    float width;
    float height;

public:

    Size() : width(0), height(0) {} // Constructeur par défaut pour éviter les erreurs
    Size(float width_, float height_) : width(width_), height(height_) {}
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    void setWidth(float w) { width = w; }
    void setHeight(float h) { height = h; }
};

#endif