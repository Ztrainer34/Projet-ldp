#include "CollisionController.hpp"
#include "../utils/Utils.hpp" // Add this include
#include "../controller/bonuses/BonusManager.hpp"

CollisionController::CollisionController(GameContext& context, ScoreManager& scoreManager, BonusManager& bonusManager) :
    gameContext_(context),
    scoreManager_(scoreManager), bonusManager_(bonusManager) {}

bool CollisionController::isBallTouchingPaddle(const Ball& ball) const{
    // Ball boundaries
    
    float ballLeft = ball.getX() - ball.getRadius();
    float ballRight = ball.getX() + ball.getRadius();
    float ballTop = ball.getY() - ball.getRadius();
    float ballBottom = ball.getY() + ball.getRadius();

    // Paddle boundaries
    auto& paddle_ = gameContext_.paddle;
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

bool CollisionController::isBallTouchingScreenBoundary(Ball& ball) const {
    
    return (ball.getX() - ball.getRadius() < 0 || ball.getX() + ball.getRadius() > CST::SCREEN_WIDTH ||
            ball.getY() - ball.getRadius() < 0 || ball.getY() + ball.getRadius() > CST::SCREEN_HEIGHT);
}

// Function to check if the ball is touching a specific block
bool CollisionController::isBallTouchingBlock(const Ball& ball, const Block& block) const {
    float brickLeft = block.getX();
    float brickRight = brickLeft + block.getWidth();
    float brickTop = block.getY();
    float brickBottom = brickTop + block.getHeight();

    // Check if the ball overlaps with the block
    
    return (ball.getX() + ball.getRadius() > brickLeft &&
            ball.getX() - ball.getRadius() < brickRight &&
            ball.getY() + ball.getRadius() > brickTop &&
            ball.getY() - ball.getRadius() < brickBottom);
}

bool CollisionController::isCapsuleTouchingPaddle(const Capsule& capsule) const{
    // Capsule's bounding box
    float capsuleLeft = capsule.getX();
    float capsuleRight = capsule.getX() + capsule.getWidth();
    float capsuleTop = capsule.getY();
    float capsuleBottom = capsule.getY() + capsule.getHeight();

        // Paddle's bounding box
    auto& paddle_ = gameContext_.paddle;
    Point paddlePos = paddle_.getPosition();
    Size paddleSize = paddle_.getSize();
    float paddleLeft = paddlePos.getX();
    float paddleRight = paddlePos.getX() + paddleSize.getWidth();
    float paddleTop = paddlePos.getY();
    float paddleBottom = paddlePos.getY() + paddleSize.getHeight();

        // Check if capsule is within the paddle_'s boundaries
    if (capsuleBottom >= paddleTop &&     // Capsule's bottom is at or below the paddle_'s top
            capsuleTop <= paddleBottom &&     // Capsule's top is at or above the paddle_'s bottom
            capsuleRight >= paddleLeft &&     // Capsule's right is at or beyond the paddle_'s left
            capsuleLeft <= paddleRight) {     // Capsule's left is at or before the paddle_'s right
            return true;                      // Collision detected
            }

    return false;   
}

bool CollisionController::isLaserTouchingBlock(const std::shared_ptr<Block> block, const Laser& laser) const{
    float laserX = laser.getX();
    float laserY = laser.getY();
    float laserWidth = laser.getWidth();
    float laserHeight = laser.getHeight();

    float blockX = block->getX();
    float blockY = block->getY();
    float blockWidth = block->getWidth();
    float blockHeight = block->getHeight();

    // Check if the laser rectangle intersects the block's rectangle
    if (laserX + laserWidth > blockX && laserX < blockX + blockWidth &&
        laserY + laserHeight > blockY && laserY < blockY + blockHeight){
            return true;
        }
    return false;
}

void CollisionController::handleBallPaddleCollision(Ball& ball){
    
    auto& paddle_ = gameContext_.paddle;

    float x = ball.getX() - (paddle_.getX() - paddle_.getWidth() / 2);

    // Length L of the paddle_
    float L = paddle_.getWidth();

    // Calculate angle alpha (in degrees)
    float alpha = 30 + 120 * (1 - x / L);

    // Convert alpha to radians
    float alpha_radians = alpha * ALLEGRO_PI / 180.0;

    // Update ball's velocity based on the new angle
    ball.setSpeedY(-ball.getSpeedY());
}

void CollisionController::handleBallScreenCollision(Ball& ball) {
    
    // Check collision with left and right walls
    if (ball.getX() - ball.getRadius() < 0) {
        // Hit the left wall
                 // Prevent the ball from going out of bounds
        ball.setX(ball.getRadius());
         // Reverse horizontal velocity
        ball.setSpeedX(-ball.getSpeedX());
    }
    else if (ball.getX() + ball.getRadius() > CST::SCREEN_WIDTH) {
        // Hit the right wall
        ball.setX(CST::SCREEN_WIDTH - ball.getRadius()); // Prevent the ball from going out of bounds
        ball.setSpeedX(-ball.getSpeedX()); 
    }

    // Check collision with top wall
    if (ball.getY() - ball.getRadius() < 0) {
        // Hit the top wall
        ball.setY(ball.getRadius()); // Prevent the ball from going out of bounds
        ball.setSpeedY(-ball.getSpeedY()); // Reverse vertical velocity
    }

    // No action needed for bottom wall in typical Arkanoid-style games, but:
    // If you want to handle bottom wall collision (e.g., lose a life):
    // Dans CollisionController, à la place de la logique de perte de vie
    // On doit utiliser un itérateur pour pouvoir supprimer sans bug
    for (auto it = gameContext_.ball_.begin(); it != gameContext_.ball_.end(); ) {
        if ((*it).getY() > Constants::SCREEN_HEIGHT) { // Si une balle sort
            
            if (gameContext_.ball_.size() > 1) {
                // S'il y a plus d'une balle, on supprime juste celle-ci
                it = gameContext_.ball_.erase(it);
            } else {
                // C'était la dernière balle, le joueur perd une vie
                gameContext_.lives--;
                (*it).resetBallPosition(); // On la réinitialise
                ++it;
            }
        } else {
            ++it;
        }
    }
}

void CollisionController::handleBallBlockCollision(Ball& ball, Block& brick) {
    if (!brick.isVisible()) return; // Skip invisible bricks

    // Get brick position_ and size
    float brickLeft = brick.getPosition().getX();
    float brickRight = brickLeft + brick.getWidth();
    float brickTop = brick.getPosition().getY();
    float brickBottom = brickTop + brick.getHeight();

    // Determine which side of the brick the ball is hitting
    
    if (ball.getY() - ball.getRadius() < brickBottom && ball.getY() + ball.getRadius() > brickTop) {
        if (ball.getX() < brickLeft || ball.getX() > brickRight) {
            ball.setSpeedX(-ball.getSpeedX()); // Reverse horizontal velocity
        } else {
            ball.setSpeedY(-ball.getSpeedY()); // Reverse vertical velocity
        }
    }
}

// Dans CollisionController::handleBallBlockCollision(Block& block)

void CollisionController::checkBallBlockCollisions(Ball& ball) {
    for (auto& block : gameContext_.blocks_) { // or level.getblocks
        if (block->isVisible() && isBallTouchingBlock(ball,*block)) {
            handleBallBlockCollision(ball, *block);

            // Le contrôleur notifie la brique qu'elle a été touchée
            block->onHit();

            // Si le coup a détruit la brique...
            if (!block->isVisible()) { 
                scoreManager_.updateScore(block->getScoreValue());

                // drop une capsule 
                bonusManager_.onBlockDestroyed(*block); 
            }
            // If you want multiple collisions in a single frame, remove this break
            break;
        }
    }
}

void CollisionController::checkCapsulePaddleCollision(){
    auto& capsules_ = gameContext_.capsules_;
    for (auto it = capsules_.begin(); it != capsules_.end(); ) {
        if (isCapsuleTouchingPaddle(**it)) {
            bonusManager_.onCapsuleCollected(**it);
            it = capsules_.erase(it); // On supprime la capsule de l'écran
        } else {
            ++it;
        }
    }
}

void CollisionController::checkLaserBlockCollisions(){
    auto& lasers_ = gameContext_.lasers;
    for (auto& laser : lasers_) {
        if (!laser.isActive()) continue;
        for (auto& block : gameContext_.blocks_) {
            if (!block->isVisible()) continue;

            // Votre logique de détection de collision (AABB) va ici
            if (isLaserTouchingBlock(block, laser)) {
                
                block->onHit();
                laser.setInactive(); // Le laser est consommé

                if (!block->isVisible()) {
                    scoreManager_.updateScore(block->getScoreValue());
                    bonusManager_.onBlockDestroyed(*block);
                }
                
                break; // Le laser ne peut détruire qu'une brique
            }
        }
    }
}

bool CollisionController::checkAllCollision(){
    bool collision = false;
    for (auto& ball: gameContext_.ball_){
        if (isBallTouchingScreenBoundary(ball)) { handleBallScreenCollision(ball); }
        if (isBallTouchingPaddle(ball)) { handleBallPaddleCollision(ball); }
        checkBallBlockCollisions(ball);
    }
   
    checkCapsulePaddleCollision();
    checkLaserBlockCollisions();
    return collision;
    
}