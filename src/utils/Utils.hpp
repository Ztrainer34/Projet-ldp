#pragma once
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <map>

struct ColorComparator {
    // Cette fonction surcharge l'opérateur () et définit comment comparer deux couleurs.
    bool operator()(const ALLEGRO_COLOR& a, const ALLEGRO_COLOR& b) const {
        if (a.r != b.r) return a.r < b.r; // on compare le rouge
        if (a.g != b.g) return a.g < b.g; // Si les rouges sont égaux, on compare le vert
        if (a.b != b.b) return a.b < b.b; 
        return a.a < b.a;
    }
};

/**
 * @brief compare 2 couleurs égaux
 */
bool colorsAreEqual(const ALLEGRO_COLOR& c1, const ALLEGRO_COLOR& c2) {
    constexpr float COLOR_EPSILON = 0.001f;
    return (std::fabs(c1.r - c2.r) < COLOR_EPSILON &&
            std::fabs(c1.g - c2.g) < COLOR_EPSILON &&
            std::fabs(c1.b - c2.b) < COLOR_EPSILON &&
            std::fabs(c1.a - c2.a) < COLOR_EPSILON);
}