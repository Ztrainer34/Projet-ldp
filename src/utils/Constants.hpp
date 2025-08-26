#pragma once

namespace Constants{
    inline constexpr float SCREEN_WIDTH = 1200.0f;
    inline constexpr float SCREEN_HEIGHT = 600.0f;
    
    inline constexpr float FALL_SPEED = 1.0f;
    inline constexpr float ZERO_VALUE = 0.0f;
    inline constexpr int BALL_SPAWN_X = 400;
    inline constexpr int BALL_SPAWN_Y = 400;
    inline constexpr float BALL_SPLIT_OFFSET = 1.0f;
    inline constexpr float BALL_SPEED_DEFAULT = 3.0f;
    inline constexpr float BALL_SPEED_SLOW = 2.0f;
    inline constexpr float BALL_RESPAWN_Y = 300.0f;
    inline constexpr int BALL_RADIUS =20;

    inline constexpr float PADDLE_BOUNCE_MIN_ANGLE = 30.0f;
    inline constexpr float PADDLE_BOUNCE_MAX_ANGLE = 150.0f;
    inline constexpr int  PADDLE_FACTOR_ENLARGE = 50;
    inline constexpr int PADDLE_SPAWN_Y = 550;
    inline constexpr int PADDLE_SIZE_X = 100;
    inline constexpr int PADDLE_SIZE_Y = 20;
    inline constexpr float PADDLE_SPEED = 300.0f;


    inline constexpr int BLOCK_SIZE_X = 70;
    inline constexpr int BLOCK_SIZE_Y = 20;
    //inline constexpr float DEG_TO_RAD = ALLEGRO_PI / 180.0;
    inline constexpr float SCREEN_BOTTOM_Y = 500.0f;

    inline constexpr float FPS = 60.0f;
    inline constexpr float START_POS = 50;
    inline constexpr float SPACING = 10;

    inline constexpr float UI_MARGIN_X = 10.0f; 
    inline constexpr float UI_MARGIN_Y = 10.0f; 
    
    inline constexpr float UI_SCORE_Y = 10.0f;
    inline constexpr float UI_LIVES_Y = 30.0f;
    inline constexpr float UI_HIGHSCORE_Y = 20.0f;
    inline constexpr float UI_HIGHSCORE_X = 20.0f;
    inline constexpr float UI_LEVEL_Y = 50.0f;

}