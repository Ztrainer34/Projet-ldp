#ifndef BONUSMANAGER_HPP
#define BONUSMANAGER_HPP

#include <vector>
#include <memory>
#include "../../model/Capsule.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"
#include "BonusContext.hpp"
#include "Bonus.hpp"

class BonusManager {
private:
    BonusContext& bonusContext_;
    std::vector<std::shared_ptr<Capsule>>& capsules_;
    std::vector<std::shared_ptr<Bonus>> active_bonuses_;

public:
    BonusManager(std::vector<std::shared_ptr<Capsule>>& capsules, BonusContext& bonusContext);
    // Update all capsules: move, check collision, apply effect, remove if needed
    void update(Paddle& paddle, Ball& ball, unsigned int& lives);
};

#endif // BONUSMANAGER_HPP 