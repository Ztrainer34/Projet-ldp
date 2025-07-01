#include "Bonus.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "BonusLaser.hpp"
#include "Level.hpp"

void Bonus::checkDuration() {
    if (active_) {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime_) >= effectDuration_) {
            deactivate();
        }
    }
}
