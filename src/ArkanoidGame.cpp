
// setup les bail dans constru

#include "ArkanoidGame.hpp"
#include <stdexcept> // Pour lancer des exceptions en cas d'erreur
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


ArkanoidGame::ArkanoidGame()
    // On utilise la liste d'initialisation pour construire les membres
    : allegroSystem_(),
      // --- Initialisation des Modèles ---
      level_(Size(70, 20), Point(50, 50), Point(10, 10)),
      ball_(Point(400, 300), 20), // 20 = radius ball a supp
      paddle_(Point(CST::SCREEN_WIDTH / 2, 550), Size(100, 20), Speed(300.0f, 0.0f), false),
      //Paddle(Point position, Size size, Speed speed, bool laser_mode);
      capsules_(),
      // --- Initialisation des Contrôleurs ---
      paddle_controller_(paddle_, lasers_, 0, CST::SCREEN_WIDTH),
      movementController_(ball_,lasers_),
      collisionController_(ball_, paddle_, level_.getBlocks(), lasers_, level_, scoreManager_,capsules_),
      scoreManager_("highscore.txt", 0, 0),
      lives_(3),
      totalBlocks_(level_.getBlocks().size()),
      font_(nullptr),
      bonusManager_(capsules_),
      gameView_()
{
    
 // --- SETUP DES OBJETS DE JEU ---
    level_.generateBlocks(level1_layout);
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
    for (const auto& block : level_.getBlocks()) {
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

ArkanoidGame::~ArkanoidGame() {
    if (font_) al_destroy_font(font_);
}

// La méthode run contient la boucle de jeu principale
void ArkanoidGame::run() {
    al_start_timer(allegroSystem_.getTimer());
    running_ = true;
    bool moveLeft = false, moveRight = false;
    while (running_) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(allegroSystem_.getEventQueue(), &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            paddle_controller_.onKeyDown(ev.keyboard.keycode);
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) running_ = false;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            paddle_controller_.onKeyUp(ev.keyboard.keycode);
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            paddle_controller_.onMouseMove(ev.mouse.x);
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running_ = false;
        }
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Paddle movement
            paddle_controller_.update(1.0 / 60.0f);
            // Ball movement
            ball_.updatePosition();
            // Bonus/capsule update
            bonusManager_.update(paddle_, ball_, lives_);
            // Collisions
            collisionController_.checkAllCollision();
            // Ball missed
            if (ball_.getY() > CST::SCREEN_HEIGHT) {
                lives_--;
                ball_.setPosition({400, 300});
            }
            // Win/lose
            if (totalBlocks_ == 0) {
                running_ = false;
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font_, al_map_rgb(255,255,255), 400, 300, ALLEGRO_ALIGN_CENTER, "YOU WIN!");
                al_flip_display();
                al_rest(2.0);
            }
            if (lives_ == 0) {
                running_ = false;
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font_, al_map_rgb(255,255,255), 400, 300, ALLEGRO_ALIGN_CENTER, "GAME OVER!");
                al_flip_display();
                al_rest(2.0);
            }
            // Render
            al_clear_to_color(al_map_rgb(0, 0, 0));
            gameView_.renderAll();
            // Draw blocks (they might need individual views)
            for (const auto& block : level_.getBlocks()) {
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
            al_draw_textf(font_, al_map_rgb(255,255,255), 10, 10, 0, "Score: %u", scoreManager_.getScore());
            al_draw_textf(font_, al_map_rgb(255,255,255), 10, 30, 0, "Lives: %u", lives_);
            al_draw_textf(font_, al_map_rgb(255,255,255), 20, 10, 0, "Highscore: %u", scoreManager_.getHighscore());
            al_flip_display();
        }
    }
}
void ArkanoidGame::initGameObject(){

}

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
        paddle_controller_.onMouseMove(ev.mouse.x);
    }
    // ... autres événements ...
    else if (ev.type == ALLEGRO_EVENT_TIMER) {
        updateGame(1.0 / 60.0); // Mettre à jour la logique

        renderGame();           // Dessiner le jeu
    }
    else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        running_ = false;
    }
}

void ArkanoidGame::updateGame(float deltaTime) {
    // Mettez ici toute la logique de mise à jour
    paddle_controller_.update(deltaTime);
    ball_.updatePosition();
    // ... ball_controller.update(), collision_controller.checkCollisions(), etc.
}

void ArkanoidGame::renderGame() {
    // Mettez ici toute la logique d'affichage
    al_clear_to_color(al_map_rgb(0, 0, 0));
    // ... paddle_view_.draw(), ball_view_.draw(), etc.
    gameView_.renderAll();
    al_draw_textf(font_, al_map_rgb(255,255,255), 10, 10, 0, "Score: %u", scoreManager_.getScore());
    al_draw_textf(font_, al_map_rgb(255,255,255), 10, 30, 0, "Lives: %u", lives_);
    al_draw_textf(font_, al_map_rgb(255,255,255), 20, 10, 0, "Highscore: %u", scoreManager_.getHighscore());
    al_flip_display();
}