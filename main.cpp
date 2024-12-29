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
    const float screen_width = 1120;
    const float screen_height = 600;
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Failed to install keyboard!\n");
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

    // Set up the display
    ALLEGRO_DISPLAY* display = al_create_display(screen_width, screen_height);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

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

    // Initialize game objects
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    Ball ball(400, 300, 3.0, 3.0, 20, blue, red);
    Paddle paddle(400, 550, 300, 100, 20, blue, red);



    const int rows = 8;               // Augmenter le nombre de lignes
    const int cols = 14;              // Augmenter le nombre de colonnes
    const float block_width = 70;     // Réduire la largeur des blocs
    const float block_height = 20;    // Réduire la hauteur des blocs
    const float spacing_x = 10;       // Espacement horizontal entre les blocs
    const float spacing_y = 10;       // Espacement vertical entre les blocs
    const float start_x = 50;         // Position initiale en X
    const float start_y = 50;         // Position initiale en Y


    std::vector<std::shared_ptr<Block>> blocks;
    for (float i = 0; i < cols; ++i) {
        for (float j = 0; j < rows; ++j) {
            float x = start_x + i * (block_width + spacing_x)-45;
            float y = start_y + j * (block_height + spacing_y);
            blocks.push_back(std::make_shared<Block>(x, y, block_width, block_height, blue, red));
        }
    }

    size_t score = 0;
    size_t lives = 3;
    size_t total_blocks = blocks.size();

    al_start_timer(timer);

    bool running = true;
    bool move_left = false, move_right = false;

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Paddle movement
            if (move_left) {
                paddle.move_left(1.0 / 60.0, 0);
            }
            if (move_right) {
                paddle.move_right(1.0 / 60.0, screen_width - 1);
            }

            // Ball movement and collisions
            ball.update_position();

            if (ball.is_touching(paddle)) {
                ball.handle_paddle_collision(paddle.get_position().x, paddle.get_size().width);
                ball.update_position();
            }

            if (ball.is_touching_screen_boundary(screen_width, screen_height)) {
                ball.handle_screen_collision(screen_width, screen_height);
            }





            // Check collisions with all blocks
            for (auto& block : blocks) {
                if (block->getVisibility() && ball.is_touching_brick(*block)) {


                    ball.handle_brick_collision(*block); // Adjust the velocity based on collision
                    score += 10;
                    total_blocks--;
                    ball.update_position();

                    // Break only if you want one collision per frame
                    // If you want multiple collisions in a single frame, remove this break
                    break;
                }
            }

            // Ensure the ball doesn't skip over blocks by adjusting its position

            if (ball.getPosition().y > screen_height) { // Ball missed
                lives--;
                ball.setPosition({400, 300});

            }

            // Check for win or lose
            if (total_blocks == 0) {
                running = false;
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, white, 400, 300, ALLEGRO_ALIGN_CENTER, "YOU WIN!");
                al_flip_display();
                al_rest(2.0);
            }

            if (lives == 0) {
                running = false;
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, white, 400, 300, ALLEGRO_ALIGN_CENTER, "GAME OVER!");
                al_flip_display();
                al_rest(2.0);
            }

            // Render objects
            al_clear_to_color(al_map_rgb(0, 0, 0));
            ball.draw();
            paddle.draw();

            for (const auto& block : blocks) {
                block->draw();
            }

            // Render score and lives
            al_draw_textf(font, white, 10, 10, 0, "Score: %zu", score);
            al_draw_textf(font, white, 10, 30, 0, "Lives: %zu", lives);

            al_flip_display();
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
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
    al_destroy_font(font);
    al_destroy_event_queue(event_queue);

    return 0;
}
//
// Created by zia on 12/28/24.
//
