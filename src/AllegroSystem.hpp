#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>

#include "model/Size.hpp"
#include "utils/Constants.hpp"

namespace CST = Constants;
class AllegroSystem{
private:
    ALLEGRO_DISPLAY* display_;
    ALLEGRO_TIMER* timer_;
    ALLEGRO_EVENT_QUEUE* event_queue_;
    bool Valid_ = true;
    
public:
    AllegroSystem();

    ALLEGRO_DISPLAY* getDisplay() const { return display_; }
    ALLEGRO_TIMER* getTimer() const { return timer_; }
    ALLEGRO_EVENT_QUEUE* getEventQueue() const { return event_queue_; }
    bool isValid() const { return Valid_; }
    
    ~AllegroSystem();

};