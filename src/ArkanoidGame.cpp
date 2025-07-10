
// setup les bail dans constru

#include "ArkanoidGame.hpp"
#include <stdexcept> // Pour lancer des exceptions en cas d'erreur


ArkanoidGame::ArkanoidGame()
    // On utilise la liste d'initialisation pour construire les membres
    : allegroSystem_(screen_width_, screen_height_),
      // --- Initialisation des Modèles ---
      ball_(Point(400, 300), 20), // 20 = radius ball a supp
      paddle_(Point(screen_width_ / 2, 550), Size(100, 20), Speed(300.0f, 0.0f), false),
      //Paddle(Point position, Size size, Speed speed, bool laser_mode);
      level_({screen_width_, screen_height_}, 8, 14, {70, 20}, 10, 10),
      capsules_(),
      // --- Initialisation des Contrôleurs ---
      paddle_controller_(paddle_, lasers_, 0, screen_width_)
      // ... initialisez les autres membres ici
{
    
 // --- SETUP DES OBJETS DE JEU ---
    level_.generateBlocks();
}



// La méthode run contient la boucle de jeu principale
void ArkanoidGame::run() {
    al_start_timer(allegroSystem_.getTimer());
    running_ = true;

    while (running_) {
        processEvents();
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
    al_flip_display();
}