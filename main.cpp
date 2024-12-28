#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <memory>
#include <cstdio>

#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"
#include "color.hpp"
#include "Score.hpp"

int main() {
    // Set up Allegro
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

    if (!al_init_font_addon()) {
        fprintf(stderr, "Failed to initialize font addon!\n");
        return -1;
    }

    // Set up the display
    printf("Avant la création de l'affichage\n");
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }
    printf("Après la création sde l'affichage\n");

    // Set up timer and evendt quehue
    printf("Avant la création du timer\n");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    if (!timer) {
        fprintf(stderr, "Failed to create timer!\n");
        al_destroy_display(display);
        return -1;
    }
    printf("Après la création du timer\n");

    printf("Avant la création de la file d'événements\n");
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Failed to create event queue!\n");
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }
    printf("Après la création de la file d'événements\n");

    printf("Avant la création de la police\n");
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        fprintf(stderr, "Failed to create built-in font!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }
    printf("Après la création de la police\n");

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Initialize game managers
    size_t score = 0;
    size_t lives = 3;

    // Initialize game objects
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);

    Point ballPosition(400, 300);
    Ball ball(ballPosition, 3.0, 3.0, 20, blue, COLOR_RED);

    Size paddleSize(100, 20);
    Point paddleCenter(400, 550);
    Paddle paddle(paddleCenter, 300, paddleSize, COLOR_BLACK, COLOR_RED);

    std::vector<std::shared_ptr<Block>> blocks;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            Point blockPosition(i * 160 + 50, j * 40 + 50);
            Size blockSize(150, 30);
            blocks.push_back(std::make_shared<Block>(blockPosition, blockSize, blue, red));
        }
    }

    size_t countBricks = blocks.size();

    al_start_timer(timer);

    bool running = true;
    bool move_left = false, move_right = false;

    while (running) {
        al_draw_textf(font, COLOR_WHITE, 700, 300, 0, "Score : %zu \n", score);
        al_draw_textf(font, COLOR_WHITE, 700, 100, 0, "Lives : %zu \n", lives);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (countBricks == 0) {
                al_draw_textf(font, COLOR_YELLOW, 500, 300, 0, "VICTOIRE ! \n");
            }

            if (move_left) {
                paddle.move_left(static_cast<float>(1.0 / 60.0), 0);
            }
            if (move_right) {
                paddle.move_right(static_cast<float>(1.0 / 60.0), 800);
            }

            ball.update_position();

            if (ball.IsBallMissed()) {
                if (lives > 1) {
                    lives--;
                    Point spawnPosition(400, 300);
                    ball.setPosition(spawnPosition);
                } else if (lives == 1) {
                    running = false;
                }
            }

            if (ball.is_touching(paddle)) {
                ball.handle_paddle_collision(paddle.get_position().x, paddle.get_size().width);
                ball.update_position();
            }
            if (ball.is_touching_screen_boundary(800, 600)) {
                ball.handle_screen_collision(800, 600);
            }
            for (auto& brick : blocks) {
                if (brick->getVisibility() && ball.is_touching_brick(*brick)) {
                    score++;
                    countBricks--;
                    ball.handle_brick_collision(*brick);
                }
            }

            al_clear_to_color(al_map_rgb(0, 0, 0));
            ball.draw();
            paddle.draw();

            for (const auto& block : blocks) {
                block->draw();
            }

            al_flip_display();
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_A || ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                move_left = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_D || ev.keyboard.keycode == ALLEGRO_KEY_P) {
                move_right = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                running = false;
            }
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_A || ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                move_left = false;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_D || ev.keyboard.keycode == ALLEGRO_KEY_P) {
                move_right = false;
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_font(font);
    al_destroy_event_queue(event_queue);

    return 0;
}
