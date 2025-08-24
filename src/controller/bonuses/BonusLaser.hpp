/**
 * @file BonusLaser.hpp
 * @brief Déclare le bonus activant le mode laser de la raquette.
 */
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

/**
 * @class BonusLaser
 * @brief Active le tir laser via la raquette tant que le bonus est actif.
 */
class BonusLaser : public Bonus {
public:
    // Constructeur
    BonusLaser(float x, float y, float speed, ALLEGRO_COLOR color);
    BonusLaser(const Point& position, float speed, ALLEGRO_COLOR color);
    BonusLaser();
       

    /** Active le mode laser dans le contexte de jeu. */
    void applyEffect(GameContext& gameContext) override;
    /** Désactive le mode laser. */
    void cancelEffect(GameContext& context) override;
    // Mise à jour de la position du laser
    void update(float deltaTime);


    // Récupère la position du laser
    const Point& getPosition() const;


private:
    Point position_;
    float speed_;
    ALLEGRO_COLOR color_;
    bool active_;
};

#endif // BONUSLASER_HPP