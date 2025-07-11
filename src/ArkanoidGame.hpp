#ifndef ARKANOIDGAME_HPP
#define ARKANOIDGAME_HPP

#include "AllegroSystem.hpp"
#include "model/Paddle.hpp"
#include "model/Laser.hpp"
#include "model/Ball.hpp"
#include "model/Block.hpp"
#include "model/Capsule.hpp"
#include "model/game/Level.hpp"


#include "controller/PaddleController.hpp"
#include "controller/CollisionController.hpp"
#include "controller/MovementController.hpp"

#include "utils/Constants.hpp"


// ... autres includes nécessaires
#include <allegro5/allegro.h>
#include <vector>
#include <memory>

namespace CST = Constants;

class ArkanoidGame {
private:
    // --- État du jeu et de la fenêtre ---
    AllegroSystem allegroSystem_;
    bool running_ = true;

    // --- Modèles (M) ---
    Ball ball_;
    Paddle paddle_; 
    std::vector<std::shared_ptr<Capsule>> capsules_;
    Level level_;
    std::vector<Laser> lasers_;
    // ... Ball, Capsules, ScoreManager, etc.

    // --- Contrôleurs (C) ---
    PaddleController paddle_controller_;
    MovementController movementController_;
    CollisionController collisionController_;

    // ... BallController, CollisionController, etc.

    // --- Vues (V) ---
    // Vous ajouterez vos objets vues ici
    // PaddleView paddle_view_;

    // --- Méthodes privées pour organiser la boucle de jeu ---
    void initGameObject();
    void processEvents();
    void updateGame(float deltaTime);
    void renderGame();

public:
    // Le constructeur fera l'initialisation
    ArkanoidGame();

    // Le destructeur fera le nettoyage
    ~ArkanoidGame();

    // La méthode publique pour lancer le jeu
    void run();
};

#endif // ARKANOIDGAME_HPP