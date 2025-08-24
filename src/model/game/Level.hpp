/**
 * @file Level.hpp
 * @brief Déclare le modèle de niveau: grille de briques et capsules.
 */
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "../Point.hpp"
#include "../Size.hpp"
#include "../Block.hpp"
#include "../GoldBlock.hpp"
#include "../SilverBlock.hpp"
#include "../Capsule.hpp"
#include "../../utils/Color.hpp"

#include <vector>
#include <memory>
#include <string>
#include <map>


// On peut le mettre dans un fichier dédié, par exemple "layouts/LevelData.hpp"

// '-' = Espace vide
// 'G' = Brique dorée
// 'S' = Brique argentée
// '1' à '8' = Briques standard de différentes couleurs

const std::vector<std::string> level1_layout = {
    "GGGGGGGGGGGGGG",
    "S-S-S-S-S-S-S-",
    "11223344556677",
    "88776655443322"
};

/**
 * @class Level
 * @brief Contient la configuration d'un niveau et gère la génération des briques.
 */
class Level {
private:
    Size screenSize_;      // Screen size
    size_t rows_;           // Number of rows of blocks
    size_t cols_;           // Number of columns of blocks
    Size blockSize_;       // Size of each block
    float spacing_x_;       // Horizontal spacing between blocks
    float spacing_y_;       // Vertical spacing between blocks
    float start_x_;
    float start_y_;
    std::vector<std::shared_ptr<Capsule>> capsules_;
    std::vector<std::shared_ptr<Block>> blocks_; // List of all blocks

public:
    // Constructor to initialize level properties
    Level(Size screenSize, size_t rows, size_t cols, Size blockSize, float spacing_x, float spacing_y);
    Level(Size blockSize, Point startPos, Point spacing);

    
    // La méthode "usine" qui lit un layout et crée les modèles de briques
    /** Génère les briques depuis un layout de caractères. */
    void generateBlocks(const std::vector<std::string>& layout);


    // Set a new level configuration

    // Get a reference to the current blocks
    /** Accès modifiable au conteneur de briques. */
    std::vector<std::shared_ptr<Block>>& getBlocks()  { return blocks_; }
    
    /** Réinitialise le niveau aux briques par défaut. */
    void resetBlocks();

     // Get a reference to the current blocks
    /** Retourne les capsules actuelles. */
    std::vector<std::shared_ptr<Capsule>> getCapsules() const {
        return capsules_;
    }

    /** Accès const aux briques. */
    const std::vector<std::shared_ptr<Block>>& get_blocks() const;

};

#endif // LEVEL_HPP
