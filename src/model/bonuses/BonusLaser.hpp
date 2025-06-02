#ifndef LASER_HPP
#define LASER_HPP

#include <allegro5/allegro.h>
#include "Point.hpp"
#include "Bonus.hpp"


class Capsule;
class Block;
class Level;
class Paddle;

class BonusLaser : public Bonus {
public:
    // Constructeur
    BonusLaser(float x, float y, float speed, ALLEGRO_COLOR color);
    BonusLaser(const Point& position, float speed, ALLEGRO_COLOR color);
       

    void applyEffect(Paddle& paddle,
                             std::vector<std::shared_ptr<BonusLaser>>& lasers,
                             std::vector<std::shared_ptr<Block>>& blocks,
                             std::vector<std::shared_ptr<Capsule>>& capsules,
                             Level& level) override;

    // Mise à jour de la position du laser
    void update(float deltaTime);

    // Dessiner le laser
    void draw() const;

    // Vérifie si le laser est actif
    bool isActive() const;

    // Récupère la position du laser
    const Point& getPosition() const;

    // Désactiver le laser
    void setInactive();

    void applyEffect(Paddle& paddle, Ball& ball) override;
    void applyEffect(Ball& ball) override ;

    void applyEffect(Paddle& paddle) override ;

    void applyEffect() override ;

    void cancelEffect(Paddle& paddle, Ball& ball) override;

    void update_position() override ;

    void checkDuration() override ;


private:
    Point position_;
    float speed_;
    ALLEGRO_COLOR color_;
    bool active_;
};

#endif // LASER_HPP