#include "Utils.hpp"

bool colorsAreEqual(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2) {
    constexpr float COLOR_EPSILON = 0.001f;
    return (std::fabs(c1.r - c2.r) < COLOR_EPSILON &&
            std::fabs(c1.g - c2.g) < COLOR_EPSILON &&
            std::fabs(c1.b - c2.b) < COLOR_EPSILON &&
            std::fabs(c1.a - c2.a) < COLOR_EPSILON);
}