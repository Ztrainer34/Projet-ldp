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
    std::shared_ptr<Bonus> currentBonus; 

public:
    BonusManager(GameContext& gameContext);
    // Update all capsules: move, check collision, apply effect, remove if needed
    void update();

    void onBlockDestroyed(const Block& block);
    void onCapsuleCollected(const Capsule& capsule);
    // pour arkanoid game
 
    
    // Getter methods
    const std::shared_ptr<Bonus> getCurrentBonus() const { return currentBonus; }
    GameContext& getGameContext() { return gameContext_; }
};

#endif // BONUSMANAGER_HPP 