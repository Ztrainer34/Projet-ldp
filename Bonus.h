#ifndef BONUS_HPP
#define BONUS_HPP

#include "Point.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include <allegro5/allegro_color.h>
#include <chrono>

class Bonus {
protected:
    Point position_;
    ALLEGRO_COLOR color_;
    bool visible_;
    bool active_; // effet actif ou pas 
    std::chrono::time_point<std::chrono::steady_clock> startTime_; 
    // Représente une horloge monotone qui ne peut pas reculer.
    const std::chrono::seconds effectDuration_ = std::chrono::seconds(10);

public:
    Bonus(const Point& position, ALLEGRO_COLOR color)
        : position_{position}, color_{color}, visible_{true} {}

    virtual void applyEffect(Paddle& paddle, Ball& ball)  = 0;
    virtual void applyEffect(Ball& ball) = 0;
    virtual void cancelEffect(Paddle& paddle, Ball& ball) = 0;

    virtual void update_position() = 0;

    virtual void activate() { active_ = true; startTime_ = std::chrono::steady_clock::now(); }
    // active et desactive le timer pour le bonus 
    virtual void deactivate() { active_ = false; }
    virtual void checkDuration() = 0;
    virtual void draw() const = 0;

    virtual ~Bonus() = default;

    //Point get_position() const { return position_; }
    //void set_position(const Point& new_position) { position_ = new_position; }
    bool is_visible() const { return visible_; }
    void set_visible(bool visible) { visible_ = visible; }
    bool isActive() const { return active_; }
};


#endif // BONUS_HPP
