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
    Point center_;
    Size size_;
    float speed_;
    ALLEGRO_COLOR frameColor_;
    ALLEGRO_COLOR fillColor_;
public:
    Paddle(Point center, float speed, float width, float height, 
        ALLEGRO_COLOR frameColor = COLOR_BLACK, ALLEGRO_COLOR fillColor = COLOR_GREY);
    void draw() override {}
    void update_position(int direction);
    void collision();
    Point get_position();
    void mouseMove(Point mouseLoc);

};

Paddle::Paddle(Point center, float speed, float width, float height, 
        ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor) : 
    center_{center}, speed_{speed}, size_{width,height}, frameColor_{frameColor}, fillColor_{fillColor}{}

Point Paddle::get_position() {
    return center_;
}

void Paddle::update_position(int direction){
    // direction 1 vers la droite
    // direction -1 vers la gauche
    center_.x += direction * speed_; 
}

void Paddle::draw() {
    float x1 = center_.x - size_.width / 2;  // center - rayon = bord gauche
    float y1 = center_.y - size_.height / 2;  // bord bas 
    float x2 = center_.x + size_.width / 2;  // bord droit 
    float y2 = center_.x + size_.height / 2;  // bord haut

    al_draw_filled_rectangle(x1, y1, x2, y2, fillColor_);

    al_draw_rectangle(x1, y1, x2, y2, frameColor_, 1);
}
