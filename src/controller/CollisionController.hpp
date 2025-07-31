
#pragma once
#include "../model/Ball.hpp"
#include "../model/Paddle.hpp"
#include "../model/Block.hpp"
#include "../model/Capsule.hpp"

#include "../model/game/Level.hpp"
#include "../model/game/Score.hpp"
#include "../utils/Constants.hpp"
#include "GameContext.hpp"
#include <vector>
#include <memory>

// Forward declaration
class BonusManager;

namespace CST = Constants;
class CollisionController {
private:
    GameContext& gameContext_;
    ScoreManager& scoreManager_;
    BonusManager& bonusManager_; // Add this line


    bool isBallTouchingPaddle(const Ball& ball) const ; // ball touch paddle
    bool isBallTouchingBlock(const Ball& ball, const Block& block) const ; // ball touch block
    bool isBallTouchingScreenBoundary(Ball& ball) const; // ball touch screen
    bool isCapsuleTouchingPaddle(const Capsule& capsule) const;
    bool isLaserTouchingBlock(const std::shared_ptr<Block> block, const Laser& laser) const;

    void handleBallPaddleCollision(Ball& ball); // collision entre la balle et la raquette
    void handleBallBlockCollision(Ball& ball, Block& brick); // collision entre la balle et une brique
    void handleBallScreenCollision(Ball& ball); // collision entre la balle et les bords de l'écran


public:
    CollisionController(GameContext& context, ScoreManager& scoreManager, BonusManager& bonusManager); // Add bonusManager to constructor
    // Détection passive (const)
    void checkBallBlockCollisions(Ball& ball);
    /**
     * @brief itere sur les capsule actif
     */
    void checkCapsulePaddleCollision();
    void checkLaserBlockCollisions();
    bool checkAllCollision();

};