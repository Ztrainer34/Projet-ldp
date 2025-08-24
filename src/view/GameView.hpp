/**
 * @file GameView.hpp
 * @brief Conteneur de vues dessinables et orchestration du rendu.
 */
#include <memory>
#include <vector>
#include "Drawable.hpp"

/**
 * @class GameView
 * @brief Gère une collection de `Drawable` et les rend dans l'ordre d'ajout.
 */
class GameView {
private:
    std::vector<std::unique_ptr<Drawable>> drawables;

public:
    /** Ajoute un élément dessinable à la scène. */
    void addRenderable(std::unique_ptr<Drawable> d) {
        drawables.push_back(std::move(d));
    }

    /** Rendu de tous les éléments dans leur ordre d'insertion. */
    void renderAll() {
        for (auto& d : drawables) {
            d->draw();
        }
    }
    
    /** Vide la scène de tous ses éléments. */
    void clearRenderables() {
        drawables.clear();
    }
};
