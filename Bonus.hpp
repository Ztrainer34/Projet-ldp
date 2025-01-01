#ifndef BONUS_H
#define BONUS_H

#include <string>
#include "Point.h"

class Bonus {
    char type_;         // Le type de bonus (ex : 'S' pour Slow, 'F' pour Fast)

    bool active_;       // Si le bonus est actif

public:
    // Constructeur
    Bonus(char type)
        : type_{type}, active_{false} {}

    // Obtenez le type de bonus
    char get_type() const { return type_; }

    // Activez ou désactivez le bonus
    void activate() { active_ = true; }
    void deactivate() { active_ = false; }

    // Vérifie si le bonus est actif
    bool is_active() const { return active_; }



    // Mise à jour de la position (chute du bonus)


    // Dessine le bonus à l'écran


    // Obtenez la position du bonus

};

#endif // BONUS_H
