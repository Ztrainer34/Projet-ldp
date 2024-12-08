#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <memory>
#include <cstdio>
#include "ball.h"
#include "paddle.h"
#include "Block.h"

int main() {
    // Set up Allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    al_install_keyboard();
    al_init_primitives_addon();

    // Set up the display
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    // Set up timer and event queue
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    if (!timer) {
        fprintf(stderr, "Failed to create timer!\n");
        return -1;
    }

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Failed to create event queue!\n");
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Initialize game objects
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);

    Ball ball(400, 300, 3.0,3.0, 20, blue, red);
    Paddle paddle(400, 550, 300, 100, 20, blue, red); // Speed set to 300 units/sec

    std::vector<std::shared_ptr<Block>> blocks;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            blocks.push_back(std::make_shared<Block>(i * 160 + 50, j * 40 + 50, 150, 30, blue, red));
        }
    }

    al_start_timer(timer);

    bool running = true;
    bool move_left = false, move_right = false; // Track key states

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Update paddle position based on key states
            if (move_left) {
                paddle.move_left(1.0 / 60.0, 0); // Boundary at left edge (x = 0)
            }
            if (move_right) {
                paddle.move_right(1.0 / 60.0, 800); // Boundary at right edge (display width = 800)
            }

            // Update ball position
            ball.update_position();

            if (ball.is_touching(paddle)) {
                ball.handle_paddle_collision(paddle.get_position().x, paddle.get_size().width);
                ball.update_position();
            }
            if (ball.is_touching_screen_boundary(800, 600)) {
                ball.handle_screen_collision(800, 600);
            }
            for (auto& brick : blocks) {
                if (brick->getVisibility() && ball.is_touching_brick(*brick)) {
                    ball.handle_brick_collision(*brick);
                    break; // Only handle one brick collision per frame
                }
            }

            // Redraw the screen
            al_clear_to_color(al_map_rgb(0, 0, 0)); // Clear screen with black
            ball.draw();
            paddle.draw();

            for (const auto& block : blocks) {
                block->draw();
            }

            al_flip_display();
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            // Handle key press
            if (ev.keyboard.keycode == ALLEGRO_KEY_A || ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                move_left = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_D || ev.keyboard.keycode == ALLEGRO_KEY_P) {
                move_right = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                running = false;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            // Handle key release
            if (ev.keyboard.keycode == ALLEGRO_KEY_A || ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                move_left = false;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_D || ev.keyboard.keycode == ALLEGRO_KEY_P) {
                move_right = false;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
    }

    // Cleanup
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return 0;
}
