#ifndef CAPSULEVIEW_HPP
#define CAPSULEVIEW_HPP

#include "../model/Capsule.hpp" 
#include "Drawable.hpp"         


class CapsuleView : public Drawable {
private:
    // Référence vers le modèle de données (le Capsule)
    const Capsule& capsule;

public:
    /**
     * @brief Constructeur de CapsuleView.
     * @param l Référence vers l'objet Capsule à dessiner.
     * @param color La couleur du Capsule.
    */
    CapsuleView(const Capsule& c, ALLEGRO_COLOR color);

    /**
     * @brief Dessine le Capsule à l'écran s'il est actif.
    */
    void draw() override;
};

#endif // CapsuleVIEW_HPP