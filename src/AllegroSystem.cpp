#include "AllegroSystem.hpp"
#include <iostream>

AllegroSystem::AllegroSystem() {
    if (!al_init() || !al_install_keyboard() || !al_install_mouse() || !al_init_primitives_addon() || !al_init_font_addon() || !al_init_ttf_addon()) {
        std::cerr << "Erreur initialisation Allegro!\n";
        Valid_ = false;
        return;
    }

    display_ = al_create_display(CST::SCREEN_WIDTH , CST::SCREEN_HEIGHT);
    if (!display_) {
        std::cerr << "Erreur création display!\n";
        Valid_ = false;
        return;
    }

    timer_ = al_create_timer(1.0 / 60.0);
    if (!timer_) {
        al_destroy_display(display_);
        std::cerr << "Erreur création timer.";
        Valid_ = false;
        return;
    }

    event_queue_ = al_create_event_queue();
    if (!event_queue_) {
        al_destroy_display(display_);
        al_destroy_timer(timer_);
        std::cerr << "Erreur création de la queue d'évènement!.";
        Valid_ = false;
        return;
    }

    al_register_event_source(event_queue_, al_get_display_event_source(display_));
    al_register_event_source(event_queue_, al_get_timer_event_source(timer_));
    al_register_event_source(event_queue_, al_get_keyboard_event_source());
    al_register_event_source(event_queue_, al_get_mouse_event_source());
}

AllegroSystem::~AllegroSystem() {
    al_destroy_display(display_);
    al_destroy_timer(timer_);
    al_destroy_event_queue(event_queue_);
}