#include "BonusManager.hpp"

#include "Bonus.hpp"

BonusManager::BonusManager(GameContext& gameContext, std::vector<std::shared_ptr<Bonus>>& bonuses)
    : gameContext_(gameContext), bonuses_(bonuses) {}

void BonusManager::update() {
    for (auto& capsule : gameContext_.capsules_) {
        if (!capsule->isVisible()) continue;
        capsule->updatePosition();
        auto& paddle = gameContext_.paddle;
        if (capsule->checkCollision(paddle)) {
            auto bonus = capsule->getBonus();
            if (bonus) {
                // Apply effect based on bonus type (example logic, adapt as needed)
                switch (bonus->get_type()) {
                    case 'E': // Enlarge
                        bonus->applyEffect(gameContext_);
                        break;
                    case 'S': // Slow
                        bonus->applyEffect(gameContext_);
                        break;
                    case 'C': // Catch
                        bonus->applyEffect(gameContext_);
                        break;
                    case 'L': // Laser
                        bonus->applyEffect(gameContext_);
                        break;
                    case 'G': // Grey/Life
                        gameContext_.lives++;
                        break;
                    // Add more cases as needed
                    default:
                        break;
                }
            }
            capsule->setVisibility(false);
        }
        if (capsule->getY() > 600) { // Assuming screen height
            capsule->setVisibility(false);
        }
    }
} 

void BonusManager::onBlockDestroyed(const Block& block){
    if (gameContext_.ball_.size() > 1) {
        return;
    }
    if (block.hasCapsule()) {
        gameContext_.capsules_.push_back(block.getCapsule());
    }
}

void BonusManager::onCapsuleCollected(const Capsule& capsule) {
    // Appliquer l'effet du bonus.
    if (auto bonus = capsule.getBonus()) {
        bonus->applyEffect(gameContext_);
        if (bonus->hasDuration()) {
            bonuses_.push_back(bonus); // ajoute dans la liste des bonus actif
        }
    }
}

void BonusManager::updateActiveBonuses() {
    // On parcourt la liste des bonus actifs
    for (auto it = bonuses_.begin(); it != bonuses_.end(); ) {
        auto& bonus = *it;
        bonus->checkDuration(); // On vérifie le temps écoulé
        
        if (!bonus->isActive()) {
            bonus->cancelEffect(gameContext_); 
            it = bonuses_.erase(it);   // on le retire de la liste
        } else {
            ++it;
        }
    }
}