#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
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
#include "Point.h" // Assuming "Point.h" exists and defines the Point class or struct

class Ball {
    Point position;
    float speed;
    float radius;
    ALLEGRO_COLOR frameColor;
    ALLEGRO_COLOR fillColor;

public:
    // Constructor
    Ball(Point position, float speed, float radius,
         ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor)
         : position(position), speed(speed), radius(radius),
           frameColor(frameColor), fillColor(fillColor) {}

    // Update the ball's position
    void update_position() {
        // Placeholder logic to update position based on speed or other parameters
        position.x += speed; // Example update, modify as needed
        position.y += speed;
    }

    // Handle collisions
    void collision() {
        // Logic to handle collisions, to be implemented
    }

    // Getters and Setters for position
    Point getPosition() const {
        return position;
    }

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void setPosition(const Point& new_position) {
        position = new_position;
    }

    // Getter and Setter for radius
    float getRadius() const {
        return radius;
    }

    void setRadius(float new_radius) {
        radius = new_radius;
    }

    // Draw the ball
    void draw() {
        al_draw_filled_circle(position.x, position.y, radius, fillColor);
        al_draw_circle(position.x, position.y, radius, frameColor, 1);
    }
};

