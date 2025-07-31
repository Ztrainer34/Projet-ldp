#include "LevelManager.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

LevelManager::LevelManager(Size blockSize, Point startPos, Point spacing)
    : currentLevelIndex_(0), blockSize_(blockSize), startPos_(startPos), spacing_(spacing) {
    currentLevel_ = std::make_shared<Level>(blockSize, startPos, spacing);
}

bool LevelManager::loadLevelFromFile(const std::string& filename) {
    try {
        std::vector<std::string> layout = parseLevelFile(filename);
        if (!layout.empty()) {
            currentLevel_->generateBlocks(layout);
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement du niveau " << filename << ": " << e.what() << std::endl;
    }
    return false;
}

bool LevelManager::loadNextLevel() {
    if (hasNextLevel()) {
        currentLevelIndex_++;
        return loadLevel(currentLevelIndex_);
    }
    return false;
}

bool LevelManager::loadLevel(size_t levelIndex) {
    if (levelIndex < levelFiles_.size()) {
        currentLevelIndex_ = levelIndex;
        return loadLevelFromFile(levelFiles_[levelIndex]);
    }
    return false;
}

bool LevelManager::hasNextLevel() const {
    return currentLevelIndex_ + 1 < levelFiles_.size();
}

std::shared_ptr<Level> LevelManager::getCurrentLevel() const {
    return currentLevel_;
}

size_t LevelManager::getCurrentLevelIndex() const {
    return currentLevelIndex_;
}

size_t LevelManager::getTotalLevels() const {
    return levelFiles_.size();
}

void LevelManager::resetToFirstLevel() {
    currentLevelIndex_ = 0;
    if (!levelFiles_.empty()) {
        loadLevel(0);
    }
}

void LevelManager::loadLevelFilesFromDirectory(const std::string& directory) {
    levelFiles_.clear();
    
    try {
        // Essayer plusieurs chemins possibles
        std::vector<std::string> possiblePaths = {
            directory,
            "../" + directory,
            "../../" + directory,
            "./" + directory
        };
        
        bool found = false;
        for (const auto& path : possiblePaths) {
            try {
                if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
                    std::cout << "Tentative de chargement depuis: " << path << std::endl;
                    
                    for (const auto& entry : std::filesystem::directory_iterator(path)) {
                        if (entry.is_regular_file() && entry.path().extension() == ".lvl") {
                            levelFiles_.push_back(entry.path().string());
                        }
                    }
                    
                    if (!levelFiles_.empty()) {
                        found = true;
                        std::cout << "Répertoire trouvé: " << path << std::endl;
                        break;
                    }
                }
            } catch (const std::exception& e) {
                std::cout << "Impossible d'accéder à " << path << ": " << e.what() << std::endl;
            }
        }
        
        if (!found) {
            throw std::runtime_error("Aucun répertoire de niveaux trouvé dans les chemins essayés");
        }
        
        // Trier les fichiers par ordre alphabétique pour un ordre prévisible
        std::sort(levelFiles_.begin(), levelFiles_.end());
        
        std::cout << "Chargement de " << levelFiles_.size() << " fichiers de niveaux" << std::endl;
        
        // Charger le premier niveau si disponible
        if (!levelFiles_.empty()) {
            loadLevel(0);
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement des fichiers de niveaux: " << e.what() << std::endl;
        // Créer un niveau par défaut si aucun fichier n'est trouvé
        std::cout << "Création d'un niveau par défaut..." << std::endl;
        createDefaultLevel();
    }
}

std::vector<std::string> LevelManager::parseLevelFile(const std::string& filename) {
    std::vector<std::string> layout;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Ignorer les lignes vides et les commentaires
        if (!line.empty() && line[0] != '#') {
            layout.push_back(line);
        }
    }
    
    file.close();
    
    if (layout.empty()) {
        throw std::runtime_error("Fichier de niveau vide ou invalide: " + filename);
    }
    
    return layout;
}

void LevelManager::createDefaultLevel() {
    // Créer un niveau par défaut simple
    std::vector<std::string> defaultLayout = {
        "GGGGGGGGGGGGGG",
        "S-S-S-S-S-S-S-",
        "11223344556677",
        "88776655443322"
    };
    
    currentLevel_->generateBlocks(defaultLayout);
    std::cout << "Niveau par défaut créé avec succès" << std::endl;
} 