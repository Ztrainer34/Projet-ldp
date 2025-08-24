/**
 * @file Block.hpp
 * @brief Déclare une brique destructible, pouvant contenir une capsule bonus.
 */
#ifndef BLOCK_H
#define BLOCK_H

#include "Object.hpp"
#include <memory>
#include <vector>
#include <allegro5/allegro.h>  // Pour ALLEGRO_COLOR et al_map_rgb()

namespace C = Constants;
// Déclarations anticipées
class Capsule;

/**
 * @class Block
 * @brief Brique de niveau avec points de vie, score, couleur et capsule optionnelle.
 */
class Block : public Object {
protected:          

    //Bonus bonus_
    bool has_capsule_ = false;              ///< Indique si une capsule est associée
    std::shared_ptr<Capsule> capsule_;      ///< Capsule éventuellement contenue
    int hitPoints_;                         ///< Points de vie restants
    unsigned int scoreValue_;               ///< Score donné à la destruction
    ALLEGRO_COLOR color_;                   ///< Couleur de la brique
    bool active = true; 

public:
    Block(Point position, Size size, bool visible, ALLEGRO_COLOR color, int hitPoints, int score);
    Block(Point position, Size size, bool visible, int hitPoints);
    // Handle collision with a ball
    
    /** @return Points de vie restants. */
    int getHp() const { return hitPoints_; } // Get the current hit count
    /** Incrémente le nombre de coups (utile si logique inverse). */
    void incrementHits() { hitPoints_++; }    // Increment the hit coun
    /** Réaction par défaut à un coup: décrémente HP et cache si 0. */
    virtual void onHit() { hitPoints_--;
                            if(hitPoints_ <= 0) setVisibility(false);  }


    /** @return Score attribué si détruite. */
    unsigned int getScoreValue() const { return scoreValue_; }

    /** @return Couleur de la brique. */
    ALLEGRO_COLOR getColor() const { return color_; }

    /** Active/désactive un état booléen générique (hérité de code antérieur). */
    void setbonus(bool bonus);
    bool getbonus() const;

    /** Associe une capsule à la brique. */
    void setCapsule(std::shared_ptr<Capsule> capsule);
    /** Retourne la capsule associée, si présente. */
    std::shared_ptr<Capsule> getCapsule() const ;
    /** Indique si une capsule est associée. */
    bool hasCapsule() const;
    /** Détruit la brique et ajoute sa capsule à la liste de chute si présente. */
    void destroy(std::vector<std::shared_ptr<Capsule>>& capsules);
    
    virtual ~Block() = default;
};

#endif // BLOCK_H