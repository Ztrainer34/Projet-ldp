
#pragma once
#include "../model/Ball.hpp"
#include "../model/Paddle.hpp"
#include "../model/Block.hpp"
#include "../model/Capsule.hpp"

#include "../model/game/Level.hpp"
#include "../model/game/Score.hpp"
#include "../utils/Constants.hpp"

#include <vector>
#include <memory>

// Forward declaration
class BonusManager;

namespace CST = Constants;
class CollisionController {
private:
    Ball& ball_;
    Paddle& paddle_;
    std::vector<std::shared_ptr<Block>>& blocks_;
    std::vector<Laser>& lasers_;
    Level& level_;
    std::vector<std::shared_ptr<Capsule>>& capsules_;

    ScoreManager& scoreManager_;
    unsigned int* lives_; // Add this line
    BonusManager& bonusManager_; // Add this line
    // BonusManager& bonus_manager_;

    bool isBallTouchingPaddle() const ; // ball touch paddle
    bool isBallTouchingBlock(const Block& block) const ; // ball touch block
    bool isBallTouchingScreenBoundary() const; // ball touch screen
    bool isCapsuleTouchingPaddle(const Capsule& capsule) const;

    void handleBallPaddleCollision(); // collision entre la balle et la raquette
    void handleBallBlockCollision(Block& brick); // collision entre la balle et une brique
    void handleBallScreenCollision(); // collision entre la balle et les bords de l'écran


public:
    CollisionController(Ball& ball, Paddle& paddle, std::vector<std::shared_ptr<Block>>& blocks, 
        std::vector<Laser>& lasers, Level& level, ScoreManager& scoreManager,
    std::vector<std::shared_ptr<Capsule>>& capsules, unsigned int* lives, BonusManager& bonusManager); // Add bonusManager to constructor
    // Détection passive (const)
    void checkBallBlockCollisions();
    void checkCapsulePaddleCollision();
    void checkLaserBlockCollisions();
    bool checkAllCollision();

};