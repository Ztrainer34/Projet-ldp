/**
 * @file Object.hpp
 * @brief Déclare la classe de base pour tous les objets du modèle (position, taille, vitesse, visibilité).
 */
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Point.hpp"
#include "Size.hpp"
#include "Speed.hpp"
#include "../utils/Constants.hpp"

namespace CST = Constants;
/**
 * @class Object
 * @brief Classe de base fournissant position, taille, vitesse et visibilité.
 *
 * Fournit des accesseurs/mutateurs et des hooks de mise à jour que les classes
 * dérivées peuvent surcharger.
 */
class Object {
protected:
    /** Position de l'objet en coordonnées écran. */
    Point position_;
    /** Dimensions de l'objet. */
    Size size_; 
    /** Vitesse (px/frame ou px/s selon usage). */
    Speed speed_;
    /** Indique si l'objet doit être considéré comme visible/actif. */
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
    
     /** Coordonnée X de la position. */
     float getX() const { return position_.getX(); }
     /** Coordonnée Y de la position. */
     float getY() const { return position_.getY(); }

     /** Retourne la position courante. */
     Point getPosition() const {
        return position_;
    }
     /** Met à jour la position. */
     void  setPosition(const Point &newPosition){
        position_ = newPosition;
    }
    /** Raccourci pour définir X et Y. */
    void setPosition(float x, float y) noexcept { position_.setPosition(x, y); }
    void setX(float x) { return position_.setX(x); }
    void setY(float y) { return position_.setY(y); }
    
    /** Taille de l'objet. */
    Size getSize() const { return size_; }
    /** Définir la taille complète. */
    void setSize(const Size& newSize) { size_ = newSize; }
    /** Largeur/hauteur. */
    float getWidth() const { return size_.getWidth(); }
    float getHeight() const { return size_.getHeight(); }
    void setWidth(float newWidth) { size_.setWidth(newWidth); }
    void setHeight(float newHeight) { size_.setHeight(newHeight); }

    /** Vitesse de l'objet. */
    Speed getSpeed() const { return speed_; }
    float getSpeedX() const { return speed_.getSpeedX(); }
    float getSpeedY() const { return speed_.getSpeedY(); }
    void setSpeed(const Speed& newSpeed) { speed_ = newSpeed; }
    void setSpeed(float x, float y) { speed_.setSpeed(x, y); }
    void setSpeedX(float x) { speed_.setSpeedX(x); }
    void setSpeedY(float y) { speed_.setSpeedY(y); }

    /** Hook générique de mise à jour (sans delta). */
    virtual void updatePosition() { }

    /** Hook générique de mise à jour (avec delta). */
    virtual void updatePosition(float delta) { } 

    /** Visibilité/activité. */
    bool isVisible() const { return visible_; };
    void setVisibility(bool newVisible) { visible_ = newVisible; }

    virtual ~Object() = default;

};
#endif // OBJECT_HPP