#ifndef BONUSMANAGER_HPP
#define BONUSMANAGER_HPP

#include <vector>
#include <memory>
#include "../../model/Capsule.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"

class BonusManager {
private:
    std::vector<std::shared_ptr<Capsule>>& capsules_;
public:
    BonusManager(std::vector<std::shared_ptr<Capsule>>& capsules);
    // Update all capsules: move, check collision, apply effect, remove if needed
    void update(Paddle& paddle, Ball& ball, unsigned int& lives);
};

#endif // BONUSMANAGER_HPP 