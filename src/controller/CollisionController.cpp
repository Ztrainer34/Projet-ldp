#include "CollisionController.hpp"
#include "../utils/Utils.hpp" // Add this include
#include "../controller/bonuses/BonusManager.hpp"

CollisionController::CollisionController(GameContext& context, Ball& ball, Paddle& paddle_, 
    std::vector<std::shared_ptr<Block>>& blocks, std::vector<Laser>& lasers, Level& level, ScoreManager& scoreManager,
    std::vector<std::shared_ptr<Capsule>>& capsules, BonusManager& bonusManager) :
    gameContext_(context),
    ball_(ball), paddle_(paddle_), blocks_(blocks), lasers_(lasers), level_(level) ,scoreManager_(scoreManager), capsules_(capsules), bonusManager_(bonusManager) {}

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

bool CollisionController::isCapsuleTouchingPaddle(const Capsule& capsule) const{
    // Capsule's bounding box
    float capsuleLeft = capsule.getX();
    float capsuleRight = capsule.getX() + capsule.getWidth();
    float capsuleTop = capsule.getY();
    float capsuleBottom = capsule.getY() + capsule.getHeight();

        // Paddle's bounding box
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
}

void CollisionController::handleBallPaddleCollision(){
    float x = ball_.getX() - (paddle_.getX() - paddle_.getWidth() / 2);

    // Length L of the paddle_
    float L = paddle_.getWidth();

    // Calculate angle alpha (in degrees)
    float alpha = 30 + 120 * (1 - x / L);

    // Convert alpha to radians
    float alpha_radians = alpha * ALLEGRO_PI / 180.0;

    // Update ball's velocity based on the new angle
    ball_.setSpeedY(-ball_.getSpeedY());
}

void CollisionController::handleBallScreenCollision() {
    auto& ball_ = gameContext_.ball;
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
        gameContext_.lives--;
        ball_.resetBallPosition();
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
}

// Dans CollisionController::handleBallBlockCollision(Block& block)

void CollisionController::checkBallBlockCollisions() {
    for (auto& block : blocks_) { // or level.getblocks
        if (block->isVisible() && isBallTouchingBlock(*block)) {
            handleBallBlockCollision(*block);

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
    for (auto it = capsules_.begin(); it != capsules_.end(); ) {
        if (isCapsuleTouchingPaddle(**it)) {
            bonusManager_.onCapsuleCollected(**it);
            it = capsules_.erase(it); // On supprime la capsule de l'écran
        } else {
            ++it;
        }
    }
}

void CollisionController::checkLaserBlockCollisions(GameContext& context){
    lasers_ = context.lasers;
    for (auto& laser : lasers_) {
        if (!laser.isActive()) continue;
        for (auto& block : context.blocks_) {
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
    if (isBallTouchingScreenBoundary()) { handleBallScreenCollision(); }
    if (isBallTouchingPaddle()) { handleBallPaddleCollision(); }
    checkBallBlockCollisions();
    checkCapsulePaddleCollision();
    checkLaserBlockCollisions(gameContext_);
    
}