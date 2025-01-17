#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include <vector>
#include <memory>
#include <cstdio>
#include <unordered_map>

#include "Block.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Capsule.h"
#include "Level.hpp"
#include "color.h"
#include "Laser.hpp"
#include <algorithm>
#include <iostream>






int main() {


    // Set up Allegro
    const float screen_width = 1200;
    const float screen_height = 600;

    const int POINTS_SILVER = 200;
    const int POINTS_OTHER = 50; // Example for other blocks
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Failed to install keyboard!\n");
        return -1;
    }
    if (!al_install_mouse()) {
        fprintf(stderr, "Failed to initialize mouse!\n");
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
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Initialize game objects


    Point ballPosition(400, 300);
    Ball ball(400, 300, 3.0, 3.0, 20, COLOR_BLUE, COLOR_RED);

    Size paddleSize(100, 20);
    Point paddleCenter(400, 550);
    Paddle paddle(400, 550, 300, 100, 20, COLOR_BLACK, COLOR_RED);

    Level level(screen_width, screen_height, 8, 14, 70, 20, 10, 10);
    std::vector<std::shared_ptr<Capsule>> capsules;
    std::vector<Laser> lasers;

    level.generate_blocks(); // genere les blocks
    std::vector<std::pair<ALLEGRO_COLOR, int>> colorScores = {
        {COLOR_WHITE, 50},
        {COLOR_ORANGE, 60},
        {COLOR_CYAN, 70},
        {COLOR_GREEN, 80},
        {COLOR_RED, 90},
        {COLOR_BLUE, 100},
        {COLOR_MAGENTA, 110},
        {COLOR_YELLOW, 120},

{COLOR_GOLD, 0},
{COLOR_SILVER, 200}
    };

    size_t score = 0;
    size_t lives = 1000;
    size_t total_blocks = level.get_blocks().size();


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
            // ici mettre le deplacement souris ?

            // Ball movement and collisions

                ball.update_position();


            for (auto& capsule : capsules) {
                // Update the capsule's position (falling downward)

                capsule->update();
                // Check for collision with the paddle
                if (capsule->checkCollision(paddle)) {
                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_BLUE)) {
                        if (capsule->isVisible()) {
                            paddle.enlarge(20);
                        }
                        capsule->setVisible(false); // Hide the capsule if it hits the paddle
                    }
                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_GREY)) {
                        if (capsule->isVisible()) {
                            lives++;
                        }

                        capsule->setVisible(false);
                    }
                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_GREEN)) {
                        if (capsule->isVisible()) {
                            paddle.enableLaserMode();

                        }




                        capsule->setVisible(false);
                    }

                }

                // If the capsule falls off the screen, make it invisible
                if (capsule->getY() > screen_height) {
                    capsule->setVisible(false);
                }

            }
            if (paddle.isLaserModeEnabled()) {
                for (auto& laser : lasers) {
                    laser.update(1.0 / 60.0);

                        for (auto& block : level.get_blocks()){
                            if (!block->getVisibility()) continue; // Ignore invisible blocks

                            float blockX = block->getPosition().x;
                            float blockY = block->getPosition().y;
                            float blockWidth = block->getSize().width;
                            float blockHeight = block->getSize().height;


                                float laserX = laser.getPosition().x;
                                float laserY = laser.getPosition().y;
                                float laserWidth = 2;   // Assuming laser width is 2 (or adjust if you have a different width)
                                float laserHeight = 10;  // Assuming laser height is 10 (or adjust if you have a different height)

                                // Check if the laser rectangle intersects the block's rectangle
                                if (laserX + laserWidth > blockX && laserX < blockX + blockWidth &&
                                    laserY + laserHeight > blockY && laserY < blockY + blockHeight) {
                                    if (laser.isActive()) {
                                        if (!block->colors_are_equals(block->getColor(),COLOR_GOLD)){
                                            block->setVisibility(false);
                                            if (block->hasCapsule()) {
                                                capsules.push_back(block->getCapsule());
                                            }
                                    }
                                }
                                        if (block->colors_are_equals(block->getColor(),COLOR_SILVER)) {

                                        }
                                    laser.setInactive();
                                    // Handle the collision here, e.g., destroy block or update score
                                    break; // Only handle the first collision per laser for now
                                    }

                        }

                }
            }

            if (ball.is_touching(paddle)) {
                ball.handle_paddle_collision(paddle.get_position().x, paddle.get_size().width);
                ball.update_position();
            }

            if (ball.is_touching_screen_boundary(screen_width, screen_height)) {
                ball.handle_screen_collision(screen_width, screen_height);
            }


            // Check collisions with all blocks
            for (auto& block : level.get_blocks()) {
                if (block->getVisibility() && ball.is_touching_brick(*block)) {



                    ALLEGRO_COLOR blockColor = block->getColor(); // recupere la couleur du block
                    for (auto it = colorScores.begin(); it != colorScores.end(); ++it){
                        if (std::next(it) == colorScores.end()) {
                            break; // Stop before the last element
                        }
                        const auto& pair = *it;
                        if(memcmp(&pair.first, &blockColor, sizeof(ALLEGRO_COLOR))==0){
                            // verifie la bonne couleur et evite les copies inutiles
                            score += pair.second;
                            break;
                        }
                        if(memcmp(&colorScores[9].first, &blockColor, sizeof(ALLEGRO_COLOR))==0) {
                            block->incrementHits();
                            if (block->getHits() == 2) {
                                score += 200;
                                break;

                            }
                            break;
                        }



                    }

                    ball.handle_brick_collision(*block); // Adjust the velocity based on collision

                    if (block->hasCapsule()) {
                        capsules.push_back(block->getCapsule());

                    }



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
                al_draw_text(font, COLOR_WHITE, 400, 300, ALLEGRO_ALIGN_CENTER, "YOU WIN!");
                al_flip_display();
                al_rest(2.0);
            }

            if (lives == 0) {
                running = false;
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(font, COLOR_WHITE, 400, 300, ALLEGRO_ALIGN_CENTER, "GAME OVER!");
                al_flip_display();
                al_rest(2.0);
            }

            // Render objects
            al_clear_to_color(al_map_rgb(0, 0, 0));
            ball.draw();
            paddle.draw(); //

            if (paddle.isLaserModeEnabled()) {
                for (const auto& laser : lasers) {
                    laser.draw();
                }
            }


            for (const auto& block : level.get_blocks()) {
                block->draw();
                if (block->hasCapsule()) {
                    block->getCapsule()->draw();

                }
            }

            // Render score and lives
            al_draw_textf(font, COLOR_WHITE, 10, 10, 0, "Score: %zu", score);
            al_draw_textf(font, COLOR_WHITE, 10, 30, 0, "Lives: %zu", lives);

            al_flip_display();
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_A || ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                move_left = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_D || ev.keyboard.keycode == ALLEGRO_KEY_P) {
                move_right = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                if (paddle.isLaserModeEnabled()) {

                    paddle.shootLaser(lasers); // Tirer un laser
                }
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
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES){
            float mouseX = static_cast<float>(ev.mouse.x);
            Point paddlePosition = paddle.get_position();


            // si souris a droite deplacer a droite
            if (mouseX > paddlePosition.x){
                paddle.move_right(1.0 / 60.0, screen_width - 1);
            }
            // si souris a gauche deplacer a gauche
            else if (mouseX < paddlePosition.x) {
                paddle.move_left(1.0 / 60.0, 0);
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
