#include "BonusManager.hpp"

#include "Bonus.hpp"

BonusManager::BonusManager(std::vector<std::shared_ptr<Capsule>>& capsules)
    : capsules_(capsules) {}

void BonusManager::update(Paddle& paddle, Ball& ball, unsigned int& lives) {
    for (auto& capsule : capsules_) {
        if (!capsule->isVisible()) continue;
        capsule->updatePosition();
        if (capsule->checkCollision(paddle)) {
            auto bonus = capsule->getBonus();
            if (bonus) {
                // Apply effect based on bonus type (example logic, adapt as needed)
                switch (bonus->get_type()) {
                    case 'E': // Enlarge
                        bonus->applyEffect(paddle);
                        break;
                    case 'S': // Slow
                        bonus->applyEffect(ball);
                        break;
                    case 'C': // Catch
                        bonus->applyEffect(paddle, ball);
                        break;
                    case 'L': // Laser
                        bonus->applyEffect(paddle);
                        break;
                    case 'G': // Grey/Life
                        lives++;
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