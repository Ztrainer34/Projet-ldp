/**
 * @file CollisionController.hpp
 * @brief Déclare le contrôleur responsable de toutes les collisions du jeu
 *        (balle/raquette, balle/brique, balle/bords, capsule/raquette, laser/brique).
 */
#pragma once
#include "../model/Ball.hpp"
#include "../model/Paddle.hpp"
#include "../model/Block.hpp"
#include "../model/Capsule.hpp"

#include "../model/game/Level.hpp"
#include "../model/game/Score.hpp"
#include "../utils/Constants.hpp"
#include "GameContext.hpp"
#include <vector>
#include <memory>

/// Déclaration anticipée du gestionnaire de bonus
class BonusManager;

/// Alias local vers l'espace de noms des constantes
namespace CST = Constants;

/**
 * @class CollisionController
 * @brief Gère la détection et la résolution des collisions entre les entités du jeu.
 *
 * Cette classe centralise toute la logique de collision afin de séparer les
 * responsabilités (moteur/contrôleur vs modèle/affichage).
 */
class CollisionController {
private:
    /** Contexte de jeu partagé (accès à la raquette, balles, niveaux, etc.). */
    GameContext& gameContext_;
    /** Référence au gestionnaire de score pour créditer les points. */
    ScoreManager& scoreManager_;
    /** Référence au gestionnaire de bonus pour déclenchement/annulation. */
    BonusManager& bonusManager_; // Add this line

    /**
     * @brief Vérifie la collision balle/raquette via AABB.
     * @param ball Balle testée.
     * @return true si la balle chevauche la raquette, false sinon.
     */
    bool isBallTouchingPaddle(const Ball& ball) const ; // ball touch paddle
    /**
     * @brief Vérifie la collision balle/brique via AABB.
     * @param ball Balle testée.
     * @param block Brique testée.
     * @return true en cas de chevauchement, false sinon.
     */
    bool isBallTouchingBlock(const Ball& ball, const Block& block) const ; // ball touch block
    /**
     * @brief Vérifie si la balle sort des limites de l'écran.
     * @param ball Balle testée (non-const car correction de position possible).
     * @return true si un bord est touché, false sinon.
     */
    bool isBallTouchingScreenBoundary(Ball& ball) const; // ball touch screen
    /**
     * @brief Vérifie la collision capsule/raquette via AABB.
     */
    bool isCapsuleTouchingPaddle(const Capsule& capsule) const;
    /**
     * @brief Vérifie la collision laser/brique via AABB.
     */
    bool isLaserTouchingBlock(const std::shared_ptr<Block> block, const Laser& laser) const;

    /**
     * @brief Résout la collision entre la balle et la raquette (rebond ou catch).
     */
    void handleBallPaddleCollision(Ball& ball); // collision entre la balle et la raquette
    /**
     * @brief Résout la collision entre la balle et une brique (rebond + dégâts).
     */
    void handleBallBlockCollision(Ball& ball, Block& brick); // collision entre la balle et une brique
    /**
     * @brief Gère les collisions de la balle avec les bords de l'écran.
     */
    void handleBallScreenCollision(Ball& ball); // collision entre la balle et les bords de l'écran


public:
    /**
     * @brief Construit le contrôleur des collisions.
     * @param context Contexte de jeu partagé.
     * @param scoreManager Gestionnaire de score.
     * @param bonusManager Gestionnaire de bonus.
     */
    CollisionController(GameContext& context, ScoreManager& scoreManager, BonusManager& bonusManager); // Add bonusManager to constructor
    // Détection passive (const)
    /**
     * @brief Vérifie et traite une collision éventuelle entre une balle et les briques visibles.
     * @param ball Balle à tester.
     */
    void checkBallBlockCollisions(Ball& ball);
    /**
     * @brief Itère sur les capsules actives et applique l'effet si elles sont collectées.
     */
    void checkCapsulePaddleCollision();
    /**
     * @brief Vérifie et applique les collisions entre lasers actifs et briques visibles.
     */
    void checkLaserBlockCollisions();
    /**
     * @brief Lance l'ensemble des tests de collisions du frame courant.
     * @return true si au moins une collision notable a eu lieu, false sinon.
     */
    bool checkAllCollision();

};