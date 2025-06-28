#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include <vector>
#include <memory>
#include <cstdio>
#include <unordered_map>
#include "Laser.hpp"
#include "Block.hpp"
#include "Ball.hpp"
#include "Bonus.hpp"
#include "BonusCatch.hpp"
#include "BonusInterruption.hpp"
#include "BonusLaser.hpp"
#include "BonusSlow.hpp"
#include "Paddle.hpp"
#include "Capsule.hpp"
#include "Level.hpp"
#include "color.hpp"
#include "Score.hpp"

#include <algorithm>
#include <iostream>


int main() {


    // Set up Allegro
    Size screenSize(1200, 600);
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
    Speed ballSpeed(3.0,3.0);
    //Ball ball(400, 300, 3.0, 3.0, 20, COLOR_BLUE, COLOR_RED);
    Ball ball(ballPosition, ballSpeed, 20, COLOR_BLUE, COLOR_RED);
    std::vector<std::shared_ptr<Ball>> balls; // liste des balles en jeu
    balls.push_back(std::make_shared<Ball>(ball)); // initialisation avec une balle

    Size paddleSize(100, 20);
    Point paddleCenter(400, 550);
    Paddle paddle(paddleCenter, 20, paddleSize, COLOR_RED, COLOR_BLUE, false);
    PaddleController paddle_controller(paddle_model, lasers, 0, screen_width);
    
    float spacing_x = 10;
    float spacing_y = 10;
    Size blockSize(70,20);
    Level level(screenSize, 8, 14, blockSize, spacing_x, spacing_y); 

    //Level level(screen_width, screen_height, 8, 14, 70, 20, 10, 10);
    std::vector<std::shared_ptr<Capsule>> capsules;
    //std::vector<BonusLaser> lasers;
    //std::vector<std::shared_ptr<BonusLaser>> lasers;
    std::vector<Laser> lasers;

    level.generateBlocks(); // genere les blocks
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
    unsigned int score_ = 0;
    unsigned int highscore = 0;
    ScoreManager score("highscore.txt", score_, highscore);
    size_t lives = 3;
    size_t totalBlocks = level.getBlocks().size();


    al_start_timer(timer);

    bool running = true;
    bool moveLeft = false, moveRight = false;

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        // ================================================================
        // SECTION 1 : GESTION DES ÉVÉNEMENTS (Redirection vers les contrôleurs)
        // ================================================================

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            paddle_controller.onKeyDown(ev.keyboard.keycode);
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                running = false;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            paddle_controller.onKeyUp(ev.keyboard.keycode);
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            paddle_controller.onMouseMove(ev.mouse.x);
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            
            // Paddle movement
            paddle_controller.update(1.0 / 60.0);
            // Ball movement and collisions

                ball.updatePosition();

            for (auto& capsule : capsules) {
                // Update the capsule's position (falling downward)

                capsule->update();
                // Check for collision with the paddle
                if (capsule->checkCollision(paddle)) { // TODO DURATION BONUS
 
                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_BLUE)) {
                        if (capsule->isVisible()) {
                            paddle.enlarge(20);  // agrandir
                            capsule->getBonus()->applyEffect(paddle);
                            capsule->getBonus()->checkDuration();
                        }
                        capsule->setVisible(false); // Hide the capsule if it hits the paddle
                    }
                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_GREY)) {
                        if (capsule->isVisible()) {
                            lives++; // joueur
                        }
                        capsule->setVisible(false);
                    }
                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_PINK)) {
                        if (capsule->isVisible()) {
                            paddle.enableLaserMode(); // laser
                        }
                        capsule->setVisible(false);
                    }
                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_GREEN)) {
                        if (capsule->isVisible()) {
                            // attraper
                            capsule->getBonus()->applyEffect(paddle, ball);  
                            capsule->getBonus()->checkDuration();    
                        }capsule->setVisible(false);
                    }

                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_ORANGE)) {
                        if (capsule->isVisible()) {
                            // slow
                            capsule->getBonus()->applyEffect(ball);      
                            capsule->getBonus()->checkDuration();
                        }capsule->setVisible(false);
                    }
                    if (capsule->colors_are_equals(capsule->getColor(),COLOR_CYAN)) {
                        if (capsule->isVisible()) {
                            // divise
                            capsule->getBonus()->applyEffect(ball);      
                            
                        }capsule->setVisible(false);
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
                                float laserWidth = 2;
                                float laserHeight = 10;


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

                                    break;
                                    }

                        }

                }
            }
    
            if (ball.isTouching(paddle)) {
                ball.handlePaddleCollision(paddle.getPosition().x, paddle.getSize().width);
                ball.updatePosition();
            }

            if (ball.isTouchingScreenBoundary(screen_width, screen_height)) {
                ball.handleScreenCollision(screen_width, screen_height);
            }


            // Check collisions with all blocks
            for (auto& block : level.getBlocks()) {
                if (block->getVisibility() && ball.isTouchingBrick(*block)) {



                    ALLEGRO_COLOR blockColor = block->getColor(); // recupere la couleur du block
                    score.updateScore(colorScores, blockColor, block);
            
                    ball.handleBrickCollision(*block); // Adjust the velocity based on collision

                    if (block->hasCapsule()) {
                        capsules.push_back(block->getCapsule());

                    }



                    totalBlocks--;
                    ball.updatePosition();

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
            if (totalBlocks == 0) {
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


            for (const auto& block : level.getBlocks()) {
                block->draw();
                if (block->hasCapsule()) {
                    block->getCapsule()->draw();

                }
            }

            // Render score and lives
            al_draw_textf(font, COLOR_WHITE, 10, 10, 0, "Score: %u", score.getScore());
            al_draw_textf(font, COLOR_WHITE, 10, 30, 0, "Lives: %zu", lives);
            al_draw_textf(font, COLOR_WHITE, 20, 10, 0, "Highscore: %u", score.getHighscore());

            al_flip_display();
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