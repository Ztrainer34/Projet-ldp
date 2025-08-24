/**
 * @file LaserView.hpp
 * @brief Vue responsable du dessin d'un laser.
 */
#ifndef LASERVIEW_HPP
#define LASERVIEW_HPP

#include "../model/Laser.hpp" // Chemin vers ton modèle Laser
#include "Drawable.hpp"         // Chemin vers ton interface Drawable


/**
 * @class LaserView
 * @brief Dessine un laser (ligne verticale) lorsque celui-ci est actif.
 */
class LaserView : public Drawable {
private:
    // Référence vers le modèle de données (le laser)
    const Laser& laser;

public:
    /**
     * @brief Constructeur de LaserView.
     * @param l Référence vers l'objet Laser à dessiner.
     * @param color La couleur du laser.
    */
    LaserView(const Laser& l, ALLEGRO_COLOR color);

    /**
     * @brief Dessine le laser à l'écran s'il est actif.
    */
    void draw() override;
};

#endif // LASERVIEW_HPP