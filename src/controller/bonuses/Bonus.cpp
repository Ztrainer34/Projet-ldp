#include "Bonus.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"
#include "BonusLaser.hpp"
#include "../../model/game/Level.hpp"

Bonus::Bonus() : type_(' '), position_(Point(0, 0)), color_(al_map_rgb(255, 255, 255)), 
                 visible_(false), active_(false), hasDuration_(false) {}

void Bonus::checkDuration() {
    if (active_) {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime_) >= effectDuration_) {
            deactivate();
        }
    }
}
