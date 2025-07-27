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

class Bonus {
protected:
    char type_;         // Le type de bonus (ex : 'S' pour Slow, 'F' pour Fast)
    Point position_;
    ALLEGRO_COLOR color_;
    bool visible_;
    bool active_; // effet actif ou pas 
    bool hasDuration_;
    std::chrono::time_point<std::chrono::steady_clock> startTime_; 
    // Représente une horloge monotone qui ne peut pas reculer.
    const std::chrono::seconds effectDuration_ = std::chrono::seconds(6);

public:
    Bonus(Point position, char type, ALLEGRO_COLOR color)
        : position_{position}, type_{type}, color_{color}, visible_{true} {}

    Bonus();
    

    virtual void applyEffect(GameContext& context) = 0;

    virtual void cancelEffect(GameContext& context){}
    // Obtenez le type de bonus
    char get_type() const { return type_; }
   

    void activate() { active_ = true; startTime_ = std::chrono::steady_clock::now(); }
    // active et desactive le timer pour le bonus 
    void deactivate() { active_ = false; }
    virtual void checkDuration();

    virtual ~Bonus() = default;

    //Point get_position() const { return position_; }
    //void set_position(const Point& new_position) { position_ = new_position; }
    bool is_visible() const { return visible_; }
    void set_visible(bool visible) { visible_ = visible; }
    bool isActive() const { return active_; }

    bool hasDuration() const { return hasDuration_; }
};


#endif // BONUS_HPP
