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

#include "color.h"

struct Point
{
    float x;
    float y;
};

class Ball{
    Point center_;
    float speed_;
    int radius_;
    ALLEGRO_COLOR frameColor_;
    ALLEGRO_COLOR fillColor_;

    public:
        Ball(Point center, float speed, int radius, 
            ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor );
        void update_position(); // to do
        void collision();  // a faire
        Point get_position();  // jsp si on a besoin
        void draw();

};

Ball::Ball(Point center, float speed, int radius,
 ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor) : center_{center},speed_{speed},
     radius_{radius},frameColor_{frameColor}, fillColor_{fillColor} {};

void Ball::draw(){

    al_draw_filled_circle(center_.x, center_.y, radius_, fillColor_);
    
    al_draw_circle(center_.x, center_.y, radius_, frameColor_, 1);
}




