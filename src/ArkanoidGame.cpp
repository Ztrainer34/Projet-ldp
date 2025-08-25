/**
 * @file ArkanoidGame.cpp
 * @brief Implémentation de la classe principale ArkanoidGame (setup, boucle, rendu).
 */

// setup les bail dans constru

#include "ArkanoidGame.hpp"
#include <stdexcept> // Pour lancer des exceptions en cas d'erreur
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream> // Added for debug print statements
#include "model/GoldBlock.hpp" // Pour détecter les blocs dorés

/**
 * @brief Construit le jeu, charge les niveaux, initialise modèles, contrôleurs et vues.
 */
ArkanoidGame::ArkanoidGame()
    // On utilise la liste d'initialisation pour construire les membres
    : allegroSystem_(),
      // --- Initialisation des Modèles ---
      levelManager_(std::make_shared<LevelManager>(Size(70, 20), Point(50, 50), Point(10, 10))),
      ball_({Ball(Point(400, 300), 20)}), // 20 = radius ball a supp
      paddle_(Point(CST::SCREEN_WIDTH / 2, 550), Size(100, 20), Speed(300.f, 0.0f), false),
      //Paddle(Point position, Size size, Speed speed, bool laser_mode);
      capsules_(),
      lasers_(),
      bonuses_(),
      
    
        lives_(3),
        totalBlocks_(0), // Set to 0 for now, will set after block generation
        colorScores_(),
        gameContext_{paddle_, ball_, lasers_, lives_, levelManager_->getCurrentLevel().get(), levelManager_->getCurrentLevel()->getBlocks(), capsules_},
      // --- Initialisation des Contrôleurs ---
      scoreManager_("highscore.txt", 0, 0),
      bonusManager_(gameContext_),
      paddle_controller_(paddle_, lasers_, 0, CST::SCREEN_WIDTH, bonusManager_),
      movementController_(gameContext_),
      
      collisionController_(gameContext_, scoreManager_, bonusManager_),
      
      
      
      font_(nullptr),
      
      gameView_()
{
    
 // --- SETUP DES OBJETS DE JEU ---
    // Charger les niveaux depuis le répertoire
    levelManager_->loadLevelFilesFromDirectory("levels");
    
    // S'assurer qu'un niveau est chargé
    if (levelManager_->getTotalLevels() == 0) {
        std::cout << "Aucun niveau trouvé, création d'un niveau par défaut" << std::endl;
    }
    
    // Compter les blocs destructibles (excluant les blocs dorés)
    size_t destructibleBlocks = 0;
    for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
        if (block->isVisible()) {
            auto goldBlock = std::dynamic_pointer_cast<GoldBlock>(block);
            if (!goldBlock) {
                destructibleBlocks++;
            }
        }
    }
    totalBlocks_ = destructibleBlocks; // Set after blocks are generated
    colorScores_ = {
        {al_map_rgb(255,255,255), 50},
        {al_map_rgb(255,165,0), 60},
        {al_map_rgb(0,255,255), 70},
        {al_map_rgb(0,255,0), 80},
        {al_map_rgb(255,0,0), 90},
        {al_map_rgb(0,0,255), 100},
        {al_map_rgb(255,0,255), 110},
        {al_map_rgb(255,255,0), 120},
        {al_map_rgb(255,215,0), 0}, // Gold
        {al_map_rgb(192,192,192), 200} // Silver
    };
    font_ = al_create_builtin_font();
    
    // Initialize view objects
   
    gameView_.addRenderable(std::make_unique<BallView>(ball_, COLOR_BLUE, COLOR_RED));
    gameView_.addRenderable(std::make_unique<PaddleView>(paddle_, COLOR_RED, COLOR_BLUE));

    // 2. Ajouter les vues pour TOUTES les briques
    for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
        // On crée une vue unique pour chaque modèle de brique
        ALLEGRO_COLOR blockColor = block->getColor();
        auto block_view = std::make_unique<BlockView>(*block, blockColor, blockColor);
        
        // On déplace la possession de cette vue vers le GameView
        gameView_.addRenderable(std::move(block_view));
    }

    // Note : Vous ferez de même pour les capsules quand elles sont créées.
    // Quand une brique est détruite et libère une capsule, vous créerez une
    // CapsuleView et l'ajouterez à gameView_.
}

/**
 * @brief Libère les ressources de police et autres si nécessaire.
 */
ArkanoidGame::~ArkanoidGame() {
    if (font_) al_destroy_font(font_);
}

// La méthode run contient la boucle de jeu principale
/**
 * @brief Boucle principale: traite les événements, met à jour, gère collisions et rendu.
 */
void ArkanoidGame::run() {
    std::cout << "[DEBUG] ArkanoidGame::run() started" << std::endl;
    al_start_timer(allegroSystem_.getTimer());
    running_ = true;
    
    while (running_) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(allegroSystem_.getEventQueue(), &ev);
        std::cout << "[DEBUG] Event type: " << ev.type << std::endl;
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            std::cout << "[DEBUG] ALLEGRO_EVENT_KEY_DOWN: " << ev.keyboard.keycode << std::endl;
            paddle_controller_.onKeyDown(ev.keyboard.keycode);
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) running_ = false;
            
            // Level switching shortcuts
            if (ev.keyboard.keycode == ALLEGRO_KEY_1) {
                switchToLevel(0);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_2) {
                switchToLevel(1);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_3) {
                switchToLevel(2);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_4) {
                switchToLevel(3);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_5) {
                switchToLevel(4);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_6) {
                switchToLevel(5);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_7) {
                switchToLevel(6);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_8) {
                switchToLevel(7);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_9) {
                switchToLevel(8);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_0) {
                switchToLevel(9);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                // Next level
                if (levelManager_->hasNextLevel()) {
                    switchToLevel(levelManager_->getCurrentLevelIndex() + 1);
                }
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                // Previous level
                if (levelManager_->getCurrentLevelIndex() > 0) {
                    switchToLevel(levelManager_->getCurrentLevelIndex() - 1);
                }
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_HOME) {
                // First level
                switchToLevel(0);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_END) {
                // Last level
                if (levelManager_->getTotalLevels() > 0) {
                    switchToLevel(levelManager_->getTotalLevels() - 1);
                }
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            std::cout << "[DEBUG] ALLEGRO_EVENT_KEY_UP: " << ev.keyboard.keycode << std::endl;
            paddle_controller_.onKeyUp(ev.keyboard.keycode);
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            std::cout << "[DEBUG] ALLEGRO_EVENT_MOUSE_AXES: x=" << ev.mouse.x << std::endl;
            paddle_controller_.onMouseMove(static_cast<float>(ev.mouse.x));
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            std::cout << "[DEBUG] ALLEGRO_EVENT_DISPLAY_CLOSE" << std::endl;
            running_ = false;
        }
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Paddle movement
            paddle_controller_.update(1.0f / 60.0f);
            // Ball movement
            for(auto& ball : gameContext_.ball_){
                ball.updatePosition();          
            }
            // Laser movement
            for (auto& laser : lasers_) {
                if (laser.isActive()) {
                    laser.updatePosition(1.0f/ 60.0f);
                }
            }
            // Bonus/capsule update
            bonusManager_.update();
            // Collisions
            collisionController_.checkAllCollision();
            // Ball missed
            for(auto& ball : gameContext_.ball_){
                if (ball.getY() > CST::SCREEN_HEIGHT) {
                    if(gameContext_.ball_.size()<1){
                        lives_--;
                    }
                    ball.setPosition({400, 300});
                }
            }
            
            // Vérifier la completion du niveau
            checkLevelCompletion();
            if (lives_ == 0) {
                running_ = false;
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font_, al_map_rgb(255,255,255), 400, 300, ALLEGRO_ALIGN_CENTER, "GAME OVER!");
                al_flip_display();
                al_rest(2.0);
            }
            // Debug print for ball position and radius
            //std::cout << "Ball position: " << ball_.getX() << ", " << ball_.getY() << " radius: " << ball_.getRadius() << std::endl;
            // Render
            al_clear_to_color(al_map_rgb(0, 0, 0));
            gameView_.renderAll();
            // Draw blocks (they might need individual views)
            for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
                if (block->isVisible()) {
                    BlockView blockView(*block, block->getColor(), block->getColor());
                    blockView.draw();
                    if (block->hasCapsule()) {
                        CapsuleView capsuleView(*block->getCapsule(), block->getCapsule()->getColor());
                        capsuleView.draw();
                    }
                }
            }
            // Draw capsules (falling bonuses)
            for (const auto& capsule : capsules_) {
                if (capsule->isVisible()) {
                    CapsuleView capsuleView(*capsule, capsule->getColor());
                    capsuleView.draw();
                }
            }
            // Draw lasers
            for (const auto& laser : lasers_) {
                if (laser.isActive()) {
                    LaserView laserView(laser, COLOR_RED);
                    laserView.draw();
                }
            }
            al_draw_textf(font_, al_map_rgb(255,255,255), 10, 10, 0, "Score: %u", scoreManager_.getScore());
            al_draw_textf(font_, al_map_rgb(255,255,255), 10, 30, 0, "Lives: %u", lives_);
            al_draw_textf(font_, al_map_rgb(255,255,255), 20, 20, 0, "Highscore: %u", scoreManager_.getHighscore());
            al_draw_textf(font_, al_map_rgb(255,255,255), 10, 50, 0, "Level: %zu/%zu", levelManager_->getCurrentLevelIndex() + 1, levelManager_->getTotalLevels());
            
            // Display level switching shortcuts
            al_draw_text(font_, al_map_rgb(255,255,255), 10, 70, 0, "Level shortcuts: 1-9,0 | Arrow keys | Home/End");
            al_flip_display();
        }
    }
}

/**
 * @brief Variante de boucle: la boucle principale ne fait que dépiler les événements.
 */
void ArkanoidGame::run2() {
    al_start_timer(allegroSystem_.getTimer());
    running_ = true;

    while (running_) {
        // La boucle principale ne fait plus qu'une seule chose : traiter les événements.
        processEvents();
    }
}

/**
 * @brief Lit un événement Allegro et redirige vers les handlers update/render.
 */
void ArkanoidGame::processEvents() {
    ALLEGRO_EVENT ev;
    al_wait_for_event(allegroSystem_.getEventQueue(), &ev);

    // Mettez ici toute la cwxhaîne if/else if pour les événements
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        paddle_controller_.onKeyDown(ev.keyboard.keycode);
        if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            running_ = false;
        }
    }
    else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        paddle_controller_.onKeyUp(ev.keyboard.keycode);
    }
    else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
        paddle_controller_.onMouseMove(static_cast<float>(ev.mouse.x));
    }
    // ... autres événements ...
    else if (ev.type == ALLEGRO_EVENT_TIMER) {
        updateGame(1.0f / 60.0f); // Mettre à jour la logique

        renderGame();           // Dessiner le jeu
    }
    else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        running_ = false;
    }
}

/**
 * @brief Met à jour la logique de jeu (mouvements, collisions, états, vies).
 */
void ArkanoidGame::updateGame(float deltaTime) {
    // Mettez ici toute la logique de mise à jour
    paddle_controller_.update(deltaTime);

    movementController_.update(); 
    collisionController_.checkAllCollision();
    if (ball_.empty()) { // Si la dernière balle est perdue
        lives_--;
        if (lives_ > 0) {
            // Remettre une balle en jeu
            ball_.push_back(Ball(Point(400, 300), 20));
        }
    }
    
    checkLevelCompletion();
    if (lives_ == 0) {
        running_ = false;
        // On pourrait gérer l'affichage de "Game Over" dans un état de jeu séparé
    }
}

/**
 * @brief Réalise le rendu complet d'une frame: fond, vues, UI.
 */
void ArkanoidGame::renderGame() {
    // Mettez ici toute la logique d'affichage
    al_clear_to_color(al_map_rgb(0, 0, 0));
    // ... paddle_view_.draw(), ball_view_.draw(), etc.
    gameView_.renderAll();
    for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
                if (block->isVisible()) {
                    BlockView blockView(*block, block->getColor(), block->getColor());
                    blockView.draw();
                    if (block->hasCapsule()) {
                        CapsuleView capsuleView(*block->getCapsule(), block->getCapsule()->getColor());
                        capsuleView.draw();
                    }
                }
            }
            // Draw capsules (falling bonuses)
            for (const auto& capsule : capsules_) {
                if (capsule->isVisible()) {
                    CapsuleView capsuleView(*capsule, capsule->getColor());
                    capsuleView.draw();
                }
            }
            // Draw lasers
            for (const auto& laser : lasers_) {
                if (laser.isActive()) {
                    LaserView laserView(laser, COLOR_RED);
                    laserView.draw();
                }
            }
    al_draw_textf(font_, al_map_rgb(255,255,255), 10, 10, 0, "Score: %u", scoreManager_.getScore());
    al_draw_textf(font_, al_map_rgb(255,255,255), 10, 30, 0, "Lives: %u", lives_);
    
    // Display level switching shortcuts

    al_flip_display();
}

/**
 * @brief Vérifie si toutes les briques destructibles sont détruites; passe au niveau suivant sinon.
 */
void ArkanoidGame::checkLevelCompletion() {
    // Compter seulement les blocs destructibles (excluant les blocs dorés)
    size_t destructibleBlocks = 0;
    for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
        if (block->isVisible()) {
            // Vérifier si c'est un bloc doré (indestructible)
            auto goldBlock = std::dynamic_pointer_cast<GoldBlock>(block);
            if (!goldBlock) {
                // Ce n'est pas un bloc doré, donc c'est destructible
                destructibleBlocks++;
            }
        }
    }
    
    // Mettre à jour le total de blocs destructibles
    totalBlocks_ = destructibleBlocks;
    
    // Si tous les blocs destructibles sont détruits, passer au niveau suivant
    if (totalBlocks_ == 0) {
        loadNextLevel();
    }
}

/**
 * @brief Charge le niveau suivant et réinitialise l'état et les vues en conséquence.
 */
void ArkanoidGame::loadNextLevel() {
    if (levelManager_->hasNextLevel()) {
        // Charger le niveau suivant
        if (levelManager_->loadNextLevel()) {
            std::cout << "Niveau " << levelManager_->getCurrentLevelIndex() << " chargé avec succès!" << std::endl;
            
            // Reset full game state on level change
            resetGameState();
            
            // Mettre à jour le contexte de jeu
            gameContext_.level = levelManager_->getCurrentLevel().get();
            gameContext_.blocks_ = levelManager_->getCurrentLevel()->getBlocks();
            
            // Mettre à jour le total de blocs destructibles
            size_t destructibleBlocks = 0;
            for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
                if (block->isVisible()) {
                    auto goldBlock = std::dynamic_pointer_cast<GoldBlock>(block);
                    if (!goldBlock) {
                        destructibleBlocks++;
                    }
                }
            }
            totalBlocks_ = destructibleBlocks;
            
            // Réinitialiser les vues pour les nouveaux blocs
            gameView_.clearRenderables();
            
            // Redessiner la balle et la raquette
            gameView_.addRenderable(std::make_unique<BallView>(ball_, COLOR_BLUE, COLOR_RED));
            gameView_.addRenderable(std::make_unique<PaddleView>(paddle_, COLOR_RED, COLOR_BLUE));
            
            // Ajouter les vues pour les nouvelles briques
            for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
                ALLEGRO_COLOR blockColor = block->getColor();
                auto block_view = std::make_unique<BlockView>(*block, blockColor, blockColor);
                gameView_.addRenderable(std::move(block_view));
            }
            
            // Réinitialiser la position de la balle
            for (auto& ball : ball_) {
                ball.setPosition({400, 300});
            }
            
            // Afficher un message de transition
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(font_, al_map_rgb(255,255,255), CST::SCREEN_WIDTH/2, CST::SCREEN_HEIGHT/2 - 20, ALLEGRO_ALIGN_CENTER, "Niveau %zu!", levelManager_->getCurrentLevelIndex() + 1);
            al_flip_display();
            al_rest(2.0);
        }
    } else {
        // Plus de niveaux disponibles - victoire finale
        running_ = false;
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_text(font_, al_map_rgb(255,255,255), CST::SCREEN_WIDTH/2, CST::SCREEN_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "FELICITATIONS! Vous avez terminé tous les niveaux!");
        al_flip_display();
        al_rest(3.0);
    }
}

/**
 * @brief Bascule vers le niveau demandé et remet l'état et les vues en phase.
 */
void ArkanoidGame::switchToLevel(size_t levelIndex) {
    if (levelIndex < levelManager_->getTotalLevels()) {
        // Charger le niveau spécifié
        if (levelManager_->loadLevel(levelIndex)) {
            std::cout << "Niveau " << levelIndex + 1 << " chargé avec succès!" << std::endl;
            
            // Reset full game state on level change
            resetGameState();
            
            // Mettre à jour le contexte de jeu
            gameContext_.level = levelManager_->getCurrentLevel().get();
            gameContext_.blocks_ = levelManager_->getCurrentLevel()->getBlocks();
            
            // Mettre à jour le total de blocs destructibles
            size_t destructibleBlocks = 0;
            for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
                if (block->isVisible()) {
                    auto goldBlock = std::dynamic_pointer_cast<GoldBlock>(block);
                    if (!goldBlock) {
                        destructibleBlocks++;
                    }
                }
            }
            totalBlocks_ = destructibleBlocks;
            
            // Réinitialiser les vues pour les nouveaux blocs
            gameView_.clearRenderables();
            
            // Redessiner la balle et la raquette
            gameView_.addRenderable(std::make_unique<BallView>(ball_, COLOR_BLUE, COLOR_RED));
            gameView_.addRenderable(std::make_unique<PaddleView>(paddle_, COLOR_RED, COLOR_BLUE));
            
            // Ajouter les vues pour les nouvelles briques
            for (const auto& block : levelManager_->getCurrentLevel()->getBlocks()) {
                ALLEGRO_COLOR blockColor = block->getColor();
                auto block_view = std::make_unique<BlockView>(*block, blockColor, blockColor);
                gameView_.addRenderable(std::move(block_view));
            }
            
            // Réinitialiser la position de la balle
            for (auto& ball : ball_) {
                ball.setPosition({400, 300});
            }
            
            // Afficher un message de transition
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(font_, al_map_rgb(255,255,255), CST::SCREEN_WIDTH/2, CST::SCREEN_HEIGHT/2 - 20, ALLEGRO_ALIGN_CENTER, "Niveau %zu!", levelManager_->getCurrentLevelIndex() + 1);
            al_flip_display();
            al_rest(1.0);
        }
    } else {
        std::cout << "Niveau " << levelIndex + 1 << " n'existe pas!" << std::endl;
    }
}

/**
 * @brief Réinitialise vies, score, paddle, balles, projectiles, capsules et contexte.
 */
void ArkanoidGame::resetGameState() {
    // Reset lives and score
    lives_ = 3;
    scoreManager_.resetScore();

    // Reset paddle
    paddle_.setPosition({CST::SCREEN_WIDTH / 2, 550});
    paddle_.setSize(Size(100, 20));
    paddle_.setSpeed(Speed(300.f, 0.0f));
    paddle_.setLaserMode(false);

    // Reset balls
    ball_.clear();
    ball_.push_back(Ball(Point(400, 300), 20));

    // Clear projectiles and capsules
    lasers_.clear();
    capsules_.clear();

    // Ensure game context references are consistent
    gameContext_.ball_ = ball_;
    gameContext_.lasers = lasers_;
    gameContext_.capsules_ = capsules_;
}