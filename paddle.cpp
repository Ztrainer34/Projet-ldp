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
#include "Drawable.cpp"
#include "Point.h"
#include "Size.h"
#include "Ball.cpp"



class Paddle : public virtual Drawable {
    Point position;
    Size size;
    int speed;
    const ALLEGRO_COLOR COLOR_GREY = al_map_rgb(200, 200, 200);

public:
    Paddle(float x, float y, int speed, float width, float height) :
    position{x,y}, speed(speed), size{width,height},COLOR_GREY(COLOR_GREY){}
    void draw() override {}
    void update_position();
    void collision();
    Point get_position();

};
