/**
 * @file GameContext.hpp
 * @brief Déclare le conteneur de références partagé entre contrôleurs du jeu.
 */
#pragma once
#include "../model/Paddle.hpp"
#include "../model/Ball.hpp"
#include "../model/game/Level.hpp"
#include "../model/Block.hpp"
#include "../model/Capsule.hpp"
#include <vector>

class Laser;

/**
 * @brief Permet de simplifier les paramètres dans les constructeurs et méthodes.
 *
 * Centralise l'accès aux entités du jeu (raquette, balles, lasers, briques,
 * capsules, niveaux, vies) afin de réduire le nombre de paramètres passés
 * aux contrôleurs.
 */
struct GameContext {
    /** Référence vers la raquette du joueur. */
    Paddle& paddle;
    /** Tableau des balles actives. */
    std::vector<Ball>& ball_;
    /** Tableau des lasers actifs. */
    std::vector<Laser>& lasers;
    /** Référence vers le compteur de vies. */
    unsigned int& lives;
    /** Pointeur vers le niveau courant (peut être nul si non initialisé). */
    Level* level;
    /** Références vers les briques présentes à l'écran. */
    std::vector<std::shared_ptr<Block>>& blocks_;
    /** Références vers les capsules présentes à l'écran. */
    std::vector<std::shared_ptr<Capsule>>& capsules_;
    
};