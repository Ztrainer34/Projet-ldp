#ifndef ARKANOIDGAME_HPP
#define ARKANOIDGAME_HPP

#include "AllegroSystem.hpp"
#include "model/Paddle.hpp"
#include "model/Laser.hpp"
#include "model/Ball.hpp"
#include "model/Block.hpp"
#include "model/Capsule.hpp"
#include "model/game/Level.hpp"
#include "model/game/Score.hpp"


#include "controller/PaddleController.hpp"
#include "controller/CollisionController.hpp"
#include "controller/MovementController.hpp"
#include "controller/bonuses/BonusManager.hpp"
#include "controller/GameContext.hpp"
#include "controller/bonuses/Bonus.hpp"

#include "utils/Constants.hpp"
#include "view/PaddleView.hpp"
#include "view/BallView.hpp"
#include "view/BlockView.hpp"
#include "view/CapsuleView.hpp"
#include "view/GameView.hpp"
#include "utils/Color.hpp"


// ... autres includes nécessaires
#include <allegro5/allegro.h>
#include <vector>
#include <memory>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>

namespace CST = Constants;

class ArkanoidGame {
private:
    // --- État du jeu et de la fenêtre ---
    AllegroSystem allegroSystem_;
    bool running_ = true;

    // --- Modèles (M) ---
    Level level_;
    Ball ball_;
    Paddle paddle_; 
    std::vector<std::shared_ptr<Capsule>> capsules_;
    std::vector<Laser> lasers_;
    std::vector<std::shared_ptr<Bonus>> bonuses_;
    ScoreManager scoreManager_;
    unsigned int lives_;
    size_t totalBlocks_;
    ALLEGRO_FONT* font_;
    std::vector<std::pair<ALLEGRO_COLOR, int>> colorScores_;
    GameContext gameContext_;
    BonusManager bonusManager_;
    GameView gameView_;
    std::vector<std::shared_ptr<Bonus>> activeBonuses_;
    GameContext gameContext_;
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