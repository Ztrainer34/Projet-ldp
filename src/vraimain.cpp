#include "ArkanoidGame.hpp"
#include "AllegroSystem.hpp"

#include <iostream> // Pour std::cerr

int main() {
    // Plus besoin de try/catch
    AllegroSystem allegroSystem(1200, 600);


    if (!allegroSystem.isValid()) {
        std::cerr << "Allegro system could not be initialized. Exiting.\n";
        return -1;
    }

    ArkanoidGame game; // On passe l'objet valide au jeu
    game.run();
    
    
    return 0;
}