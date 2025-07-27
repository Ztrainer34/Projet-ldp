#ifndef BONUSLASER_HPP
#define BONUSLASER_HPP

#include <allegro5/allegro.h>
#include "../../model/Point.hpp"
#include "../../utils/Utils.hpp"
#include "../../model/game/Level.hpp"
#include "Bonus.hpp"


class Capsule;
class Block;
class Level;
class Paddle;
class GameContext;

class BonusLaser : public Bonus {
public:
    // Constructeur
    BonusLaser(float x, float y, float speed, ALLEGRO_COLOR color);
    BonusLaser(const Point& position, float speed, ALLEGRO_COLOR color);
    BonusLaser();
       

    void applyEffect(GameContext& gameContext) override;
    // Mise à jour de la position du laser
    void update(float deltaTime);

    // Vérifie si le laser est actif
    bool isActive() const;

    // Récupère la position du laser
    const Point& getPosition() const;

    // Désactiver le laser
    void setInactive();
  
    //void checkDuration() override ;


private:
    Point position_;
    float speed_;
    ALLEGRO_COLOR color_;
    bool active_;
};

#endif // BONUSLASER_HPP