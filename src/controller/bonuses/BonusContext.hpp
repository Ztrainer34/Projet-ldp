#pragma once
#pragma once
#include "../model/Paddle.hpp"
#include "../model/Ball.hpp"
#include "../model/Laser.hpp"
#include <vector>

struct BonusContext {
    Paddle& paddle;
    Ball& ball;
    std::vector<Laser>& lasers;
    unsigned int& lives;
    Level& level;
};