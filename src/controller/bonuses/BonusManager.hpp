#ifndef BONUSMANAGER_HPP
#define BONUSMANAGER_HPP

#include <vector>
#include <memory>
#include "../../model/Capsule.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"
#include "../../model/Block.hpp"
#include "../GameContext.hpp"
#include "Bonus.hpp"

class BonusManager {
private:
    GameContext& gameContext_;
    std::vector<std::shared_ptr<Capsule>>& capsules_;
    std::vector<std::shared_ptr<Bonus>>& bonuses_;

public:
    BonusManager(std::vector<std::shared_ptr<Capsule>>& capsules, GameContext& gameContext, std::vector<std::shared_ptr<Bonus>>& bonuses);
    // Update all capsules: move, check collision, apply effect, remove if needed
    void update(Paddle& paddle, Ball& ball, unsigned int& lives);

    void onBlockDestroyed(const Block& block);
    void onCapsuleCollected(const Capsule& capsule);

};

#endif // BONUSMANAGER_HPP 