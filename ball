#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include <allegro5/mouse.h>
#include <allegro5/system.h>
#include <allegro5/timer.h>
#include <allegro5/transformations.h>

struct Point
{
    float x;
    float y;
};

class Ball{
    Point position;
    const ALLEGRO_COLOR COLOR_RED  = al_map_rgb(255, 0, 0);
    
    int speed;
    int radius;
    Ball(float x, float y, int speed, int radius) : position{x,y},speed(speed),
     radius(radius), COLOR_RED(COLOR_RED){};

    public:
        void update_position();
        void collision();

};


