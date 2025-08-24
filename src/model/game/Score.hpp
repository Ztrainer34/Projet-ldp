/**
 * @file Score.hpp
 * @brief Déclare le gestionnaire de score et highscore (persistant).
 */
#ifndef SCORE_HPP
#define SCORE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <allegro5/allegro.h> 
#include <allegro5/allegro_color.h>
#include "../../utils/Utils.hpp"



class Block;

/**
 * @class ScoreManager
 * @brief Gère le score courant, le highscore et leur persistance.
 */
class ScoreManager {
private:
    unsigned int score_ = 0;
    unsigned int highscore_ = 0;
    std::string highscoreFile_;
    std::vector<std::shared_ptr<Block>> blocks_; // List of all blocks
    

public:
    ScoreManager(const std::string& file, unsigned int score, unsigned int highscore);
    ~ScoreManager();

    /** Charge le highscore depuis le fichier associé. */
    void loadHighscore(); // preserve le highscore entre plusieurs partie
    /** Sauvegarde le highscore actuel dans le fichier. */
    void saveHighscore();
    /** Ajoute des points et met à jour le highscore si nécessaire. */
    void updateScore(unsigned int pts);
    /** Highscore courant. */
    unsigned int getHighscore() const;
    /** Score courant. */
    unsigned int getScore() const;
    /** Définit explicitement le highscore. */
    void setHighscore(unsigned int newScore);
    /** Remet le score à zéro. */
    void resetScore(){ score_ = 0; }

    /** Accès aux blocs (si nécessaire pour affichage/logique). */
    std::vector<std::shared_ptr<Block>>& get_blocks() { return blocks_; }

};

#endif //SCORE_HPP