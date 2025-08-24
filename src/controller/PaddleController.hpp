/**
 * @file PaddleController.hpp
 * @brief Déclare le contrôleur d'entrées et d'actions liées à la raquette.
 */
#pragma once
#include <algorithm> // pour std::max/min
#include <allegro5/allegro.h> 
#include "../model/Paddle.hpp"
#include "bonuses/BonusManager.hpp"

/**
 * @class PaddleController
 * @brief Gère les entrées clavier/souris et les actions de la raquette.
 */
class PaddleController {
private:
    /** Référence vers la raquette contrôlée. */
    Paddle& paddle_;
    /** Référence vers le conteneur des lasers tirés. */
    std::vector<Laser>& lasers_;
    /** Bord gauche autorisé pour la raquette. */
    float boundary_left_;
    /** Bord droit autorisé pour la raquette. */
    float boundary_right_;
    /** Gestionnaire de bonus pour interagir avec les états liés aux bonus. */
    BonusManager& bonusManager_;

    bool moving_left_ = false;   ///< Indique si un mouvement vers la gauche est en cours
    bool moving_right_ = false;  ///< Indique si un mouvement vers la droite est en cours
    bool shoot_requested_ = false; ///< Demande de tir laser (consommée à l'update)
    bool launch_requested_ = false; ///< Demande de lancer la balle (mode catch)

public:
    /**
     * @brief Construit le contrôleur de raquette.
     * @param p Référence vers la raquette.
     * @param l Référence vers le tableau des lasers.
     * @param left Limite gauche.
     * @param right Limite droite.
     * @param bm Gestionnaire de bonus.
     */
    PaddleController(Paddle& p, std::vector<Laser>& l,
                     float left, float right, BonusManager& bm)
      : paddle_(p), lasers_(l),
        boundary_left_(left), boundary_right_(right), bonusManager_(bm) {}

    // Méthodes pour que la boucle main nous informe des événements
    /**
     * @brief Notification d'appui sur une touche.
     * @param keycode Code Allegro de la touche.
     */
    void onKeyDown(int keycode);
    /**
     * @brief Notification de relâchement d'une touche.
     * @param keycode Code Allegro de la touche.
     */
    void onKeyUp(int keycode);
    /**
     * @brief Notification de déplacement de la souris (contrôle fin de la raquette).
     * @param mouseX Position X de la souris.
     */
    void onMouseMove(float mouseX);
    /**
     * @brief Met à jour la raquette et traite les demandes (tir, lancement).
     * @param deltaTime Temps écoulé depuis la dernière frame (secondes).
     */
    void update(float deltaTime);

    /** Active le mode laser sur la raquette. */
    void activateLaserBonus();
    /** Lance la balle si elle est actuellement "attrapée" (bonus catch). */
    void launchBall();
};
