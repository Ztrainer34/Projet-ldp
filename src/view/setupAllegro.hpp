#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include "../model/core/Size.hpp"

class SetupAllegro{
private:
public:
    SetupAllegro();

    int alInit();

    ALLEGRO_DISPLAY* setupDisplay(const Size& screen);

    int setupEvent(ALLEGRO_DISPLAY* display);
    

};