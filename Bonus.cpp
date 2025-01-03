#include "Bonus.h"

void Bonus::checkDuration() {
    if (active_) {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime_) >= effectDuration_) {
            deactivate();
        }
    }
}
