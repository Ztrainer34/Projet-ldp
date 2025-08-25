/**
 * @file Bonus.hpp
 * @brief Déclare la classe de base abstraite pour tous les bonus.
 */
#ifndef BONUS_HPP
#define BONUS_HPP

#include "../../model/Object.hpp"
#include "../../model/Point.hpp"


#include <allegro5/allegro_color.h>
#include <chrono>
#include <vector>
#include <memory>

class Paddle;
class Ball;
class Block;
class Capsule;
class BonusLaser; 
class Level;
class GameContext;

/**
 * @class Bonus
 * @brief Interface de base pour les bonus. Fournit activation, annulation et type.
 */
class Bonus {
protected:
    char type_;         // Le type de bonus (ex : 'S' pour Slow, 'F' pour Fast)
    Point position_;
    ALLEGRO_COLOR color_;
    bool visible_;
    bool active_; // effet actif ou pas 

public:
    /**
     * @brief Construit un bonus générique.
     * @param position Position initiale.
     * @param type Code du type (ex: 'S', 'E', 'L', 'C').
     * @param color Couleur associée.
     */
    Bonus(Point position, char type, ALLEGRO_COLOR color)
        : type_{type}, position_{position}, color_{color}, visible_{true}, active_{false} {}

    Bonus();
    

    /**
     * @brief Applique l'effet du bonus au contexte de jeu.
     */
    virtual void applyEffect(GameContext& context) = 0;

    /**
     * @brief Annule l'effet (par défaut: désactive le bonus).
     */
    virtual void cancelEffect([[maybe_unused]] GameContext& context){ deactivate(); }
    /** @brief Type de bonus. */
    char get_type() const { return type_; }
   

    /** Active le bonus. */
    void activate() { active_ = true; }
    /** Active/désactive le bonus. */
    void deactivate() { active_ = false; }
    

    virtual ~Bonus() = default;

    //Point get_position() const { return position_; }
    //void set_position(const Point& new_position) { position_ = new_position; }
    /** Indique si l'entité associée est visible. */
    bool is_visible() const { return visible_; }
    /** Modifie la visibilité. */
    void set_visible(bool visible) { visible_ = visible; }
    /** Indique si l'effet est actif. */
    bool isActive() const { return active_; }

};


#endif // BONUS_HPP
