#include "Bonus.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"
#include "BonusLaser.hpp"
#include "../../model/game/Level.hpp"

Bonus::Bonus() 
    : type_('?'), visible_(true), active_(false), color_(COLOR_YELLOW) , hasDuration_(false) {} // par defaut

void Bonus::checkDuration() {
    if (active_) {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime_) >= effectDuration_) {
            deactivate();
        }
    }
}
