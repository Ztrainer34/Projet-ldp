#include "setupAllegro.hpp"
#include <iostream>

int SetupAllegro::alInit(){
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Failed to install keyboard!\n");
        return -1;
    }
    if (!al_install_mouse()) {
        fprintf(stderr, "Failed to initialize mouse!\n");
        return -1;
    }


    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Failed to initialize primitives addon!\n");
        return -1;
    }

    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        fprintf(stderr, "Failed to initialize font addons!\n");
        return -1;
    }
    return 0;
}

ALLEGRO_DISPLAY* SetupAllegro::setupDisplay(const Size& screen){
    ALLEGRO_DISPLAY* display = al_create_display(screen.getWidth(), screen.getHeight());
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return nullptr;
    }
    return display;
}

int SetupAllegro::setupEvent(ALLEGRO_DISPLAY* display){
    // Set up timer and event queue
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();

    if (!timer || !event_queue || !font) {
        fprintf(stderr, "Failed to initialize timer, event queue, or font!\n");
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    return 0;
}