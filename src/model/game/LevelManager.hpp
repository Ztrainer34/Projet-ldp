#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include "Level.hpp"
#include <vector>
#include <string>
#include <memory>

class LevelManager {
private:
    std::vector<std::string> levelFiles_;
    size_t currentLevelIndex_;
    std::shared_ptr<Level> currentLevel_;
    Size blockSize_;
    Point startPos_;
    Point spacing_;

public:
    LevelManager(Size blockSize, Point startPos, Point spacing);
    
    // Charge un niveau depuis un fichier
    bool loadLevelFromFile(const std::string& filename);
    
    // Charge le niveau suivant
    bool loadNextLevel();
    
    // Charge un niveau spécifique par index
    bool loadLevel(size_t levelIndex);
    
    // Vérifie si il y a un niveau suivant
    bool hasNextLevel() const;
    
    // Obtient le niveau actuel
    std::shared_ptr<Level> getCurrentLevel() const;
    
    // Obtient l'index du niveau actuel
    size_t getCurrentLevelIndex() const;
    
    // Obtient le nombre total de niveaux
    size_t getTotalLevels() const;
    
    // Réinitialise au premier niveau
    void resetToFirstLevel();
    
    // Charge tous les fichiers de niveaux depuis un répertoire
    void loadLevelFilesFromDirectory(const std::string& directory);

private:
    // Parse un fichier de niveau et retourne le layout
    std::vector<std::string> parseLevelFile(const std::string& filename);
    
    // Crée un niveau par défaut si aucun fichier n'est trouvé
    void createDefaultLevel();
};

#endif // LEVELMANAGER_HPP 