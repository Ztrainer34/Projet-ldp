#ifndef ARKANOIDGAME_HPP
#define ARKANOIDGAME_HPP

#include "AllegroSystem.hpp"
#include "model/Paddle.hpp"
#include "model/Laser.hpp"
#include "model/Ball.hpp"
#include "model/Block.hpp"
#include "model/Capsule.hpp"
#include "model/game/Level.hpp"
#include "model/game/LevelManager.hpp"
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
#include "view/LaserView.hpp"
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
    std::shared_ptr<LevelManager> levelManager_;
    std::vector<Ball> ball_; 
    Paddle paddle_; 
    std::vector<std::shared_ptr<Capsule>> capsules_;
    std::vector<Laser> lasers_;
    std::vector<std::shared_ptr<Bonus>> bonuses_;
    unsigned int lives_;
    size_t totalBlocks_;
    
    std::vector<std::pair<ALLEGRO_COLOR, int>> colorScores_;
    GameContext gameContext_;
    ScoreManager scoreManager_;
    BonusManager bonusManager_;
    
    

    // ... Ball, Capsules, ScoreManager, etc.

    // --- Contrôleurs (C) ---
    PaddleController paddle_controller_;
    MovementController movementController_;
    CollisionController collisionController_;

    // ... BallController, CollisionController, etc.

    // --- Vues (V) ---
    ALLEGRO_FONT* font_;
    GameView gameView_;
    // Vous ajouterez vos objets vues ici
    // PaddleView paddle_view_;

    // --- Méthodes privées pour organiser la boucle de jeu ---
    
    void processEvents();
    void updateGame(float deltaTime);
    void renderGame();
    void checkLevelCompletion();
    void loadNextLevel();
    void switchToLevel(size_t levelIndex);

public:
    // Le constructeur fera l'initialisation
    ArkanoidGame();

    // Le destructeur fera le nettoyage
    ~ArkanoidGame();

    // La méthode publique pour lancer le jeu
    void run();
    void run2();
};

#endif // ARKANOIDGAME_HPP