#pragma once
#include "../model/Paddle.hpp"
#include "../model/Ball.hpp"
#include "../model/game/Level.hpp"
#include "../model/Block.hpp"
#include "../model/Capsule.hpp"
#include <vector>

class Laser;

/**
 * @brief permet de simplifier les param dans les constructeurs, méthodes
 */
struct GameContext {
    Paddle& paddle;
    std::vector<Ball>& ball_;
    std::vector<Laser>& lasers;
    unsigned int& lives;
    Level* level;
    std::vector<std::shared_ptr<Block>>& blocks_;
    std::vector<std::shared_ptr<Capsule>>& capsules_;
    
};