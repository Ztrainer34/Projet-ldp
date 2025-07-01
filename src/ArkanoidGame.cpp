
// setup les bail dans constru

#include "ArkanoidGame.hpp"
#include <stdexcept> // Pour lancer des exceptions en cas d'erreur

// Le constructeur EST votre méthode "init" et "setup" !
ArkanoidGame::ArkanoidGame()
    // On utilise la liste d'initialisation pour construire les membres
    : display_(nullptr),
      timer_(nullptr),
      event_queue_(nullptr),
      // --- Initialisation des Modèles ---
      paddle_({screen_width_ / 2, 550}, {100, 20}, 300.0f, false),
      level_({screen_width_, screen_height_}, 8, 14, {70, 20}, 10, 10),
      // --- Initialisation des Contrôleurs ---
      paddle_controller_(paddle_, lasers_, 0, screen_width_)
      // ... initialisez les autres membres ici
{
    // --- SETUP ALLEGRO ---
    // Tout le code al_init... va ici. S'il y a une erreur, on lance une exception.
    if (!al_init() || !al_install_keyboard() || !al_install_mouse() || !al_init_primitives_addon()) {
        throw std::runtime_error("Failed to initialize Allegro addons.");
    }
    
    display_ = al_create_display(screen_width_, screen_height_);
    if (!display_) {
        throw std::runtime_error("Failed to create display.");
    }

    timer_ = al_create_timer(1.0 / 60.0);
    event_queue_ = al_create_event_queue();

    // ... reste de la configuration d'Allegro (enregistrement des sources, etc.)
    al_register_event_source(event_queue_, al_get_display_event_source(display_));
    al_register_event_source(event_queue_, al_get_timer_event_source(timer_));
    al_register_event_source(event_queue_, al_get_keyboard_event_source());
    al_register_event_source(event_queue_, al_get_mouse_event_source());

    // --- SETUP DES OBJETS DE JEU ---
    level_.generateBlocks();
}

// Le destructeur s'occupe de tout nettoyer proprement
ArkanoidGame::~ArkanoidGame() {
    al_destroy_display(display_);
    al_destroy_timer(timer_);
    al_destroy_event_queue(event_queue_);
    // Allegro s'occupe de désinstaller les addons à la fin du programme
}

// La méthode run contient la boucle de jeu principale
void ArkanoidGame::run() {
    al_start_timer(timer_);
    running_ = true;

    while (running_) {
        processEvents(); // Gère les entrées
        // La logique de update/render est souvent liée au timer
    }
}

void ArkanoidGame::initGameObject(){

}

void ArkanoidGame::processEvents() {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue_, &ev);

    // Mettez ici toute la chaîne if/else if pour les événements
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        paddle_controller_.onKeyDown(ev.keyboard.keycode);
        if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            running_ = false;
        }
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
    // ... ball_controller.update(), collision_controller.checkCollisions(), etc.
}

void ArkanoidGame::renderGame() {
    // Mettez ici toute la logique d'affichage
    al_clear_to_color(al_map_rgb(0, 0, 0));
    // ... paddle_view_.draw(), ball_view_.draw(), etc.
    al_flip_display();
}