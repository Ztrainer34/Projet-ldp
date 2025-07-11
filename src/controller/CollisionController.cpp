#include "CollisionController.hpp"

CollisionController::CollisionController(Ball& ball, Paddle& paddle, 
    std::vector<std::shared_ptr<Block>>& blocks, std::vector<Laser>& lasers, Level& level) :
    ball_(ball), paddle_(paddle), blocks_(blocks), lasers_(lasers), level_(level) {}

bool CollisionController::isBallTouchingPaddle() const{
    // Ball boundaries
    float ballLeft = ball_.getX() - ball_.getRadius();
    float ballRight = ball_.getX() + ball_.getRadius();
    float ballTop = ball_.getY() - ball_.getRadius();
    float ballBottom = ball_.getY() + ball_.getRadius();

    // Paddle boundaries
    float paddleLeft = paddle_.getX() - paddle_.getWidth() / 2;
    float paddleRight = paddle_.getX() + paddle_.getWidth() / 2;
    float paddleTop = paddle_.getY() - paddle_.getHeight() / 2;
    float paddleBottom = paddle_.getY() + paddle_.getHeight() / 2;

    // Check for overlap
    return ballRight >= paddleLeft &&
           ballLeft <= paddleRight &&
           ballBottom >= paddleTop &&
           ballTop <= paddleBottom;
}

bool CollisionController::isBallTouchingScreenBoundary() const {
    return (ball_.getX() - ball_.getRadius() < 0 || ball_.getX() + ball_.getRadius() > CST::SCREEN_WIDTH ||
            ball_.getY() - ball_.getRadius() < 0 || ball_.getY() + ball_.getRadius() > CST::SCREEN_HEIGHT);
}

// Function to check if the ball is touching a specific block
bool CollisionController::isBallTouchingBlock(const Block& block) const {
    // Get block position_ and size
    float brickLeft = block.getX();
    float brickRight = brickLeft + block.getWidth();
    float brickTop = block.getY();
    float brickBottom = brickTop + block.getHeight();

    // Check if the ball overlaps with the block
    return (ball_.getX() + ball_.getRadius() > brickLeft &&
            ball_.getX() - ball_.getRadius() < brickRight &&
            ball_.getY() + ball_.getRadius() > brickTop &&
            ball_.getY() - ball_.getRadius() < brickBottom);
}

void CollisionController::handleBallPaddleCollision(){
    float x = ball_.getX() - (paddle_.getX() - paddle_.getWidth() / 2);

    // Length L of the paddle
    float L = paddle_.getWidth();

    // Calculate angle alpha (in degrees)
    float alpha = 30 + 120 * (1 - x / L);

    // Convert alpha to radians
    float alpha_radians = alpha * ALLEGRO_PI / 180.0;

    // Update ball's velocity based on the new angle
    ball_.setSpeedY(-ball_.getSpeedY());

    ball_.updatePosition();
}

void CollisionController::handleBallScreenCollision() {
    // Check collision with left and right walls
    if (ball_.getX() - ball_.getRadius() < 0) {
        // Hit the left wall
                 // Prevent the ball from going out of bounds
        ball_.setX(ball_.getRadius());
         // Reverse horizontal velocity
        ball_.setSpeedX(-ball_.getSpeedX());
    }
    else if (ball_.getX() + ball_.getRadius() > CST::SCREEN_WIDTH) {
        // Hit the right wall
        ball_.setX(CST::SCREEN_WIDTH - ball_.getRadius()); // Prevent the ball from going out of bounds
        ball_.setSpeedY(-ball_.getSpeedY()); // Reverse horizontal velocity
    }

    // Check collision with top wall
    if (ball_.getY() - ball_.getRadius() < 0) {
        // Hit the top wall
        ball_.setY(ball_.getRadius()); // Prevent the ball from going out of bounds
        ball_.setSpeedY(-ball_.getSpeedY()); // Reverse vertical velocity
    }

    // No action needed for bottom wall in typical Arkanoid-style games, but:
    // If you want to handle bottom wall collision (e.g., lose a life):
    if (ball_.getY() + ball_.getRadius() > CST::SCREEN_HEIGHT) {
        // The ball has hit the bottom of the screen (you can handle this as needed)
        // For example: reset ball position_ or decrease player life
        //todo !
    }
}

void CollisionController::handleBallBlockCollision(Block& brick) {
    if (!brick.isVisible()) return; // Skip invisible bricks

    // Get brick position_ and size
    float brickLeft = brick.getPosition().getX();
    float brickRight = brickLeft + brick.getWidth();
    float brickTop = brick.getPosition().getY();
    float brickBottom = brickTop + brick.getHeight();

    // Determine which side of the brick the ball is hitting
    if (ball_.getY() - ball_.getRadius() < brickBottom && ball_.getY() + ball_.getRadius() > brickTop) {
        if (ball_.getX() < brickLeft || ball_.getX() > brickRight) {
            ball_.setSpeedX(-ball_.getSpeedX()); // Reverse horizontal velocity
        } else {
            ball_.setSpeedY(-ball_.getSpeedY()); // Reverse vertical velocity
        }
    }

    // Mark the brick as no longer visible
    brick.setVisibility(false);
}

bool CollisionController::checkAllCollision(){
    if (isBallTouchingScreenBoundary()) { handleBallScreenCollision(); }
    if (isBallTouchingPaddle()) { handleBallPaddleCollision(); }

    for (auto& block : level_.getBlocks()) {
        if (block->isVisible() && isBallTouchingBlock(*block)) {
            ALLEGRO_COLOR blockColor = block->getColor(); // recupere la couleur du block
            score.updateScore(colorScores, blockColor, block);
            
            handleBallBlockCollision(*block); // Adjust the velocity based on collision

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

}