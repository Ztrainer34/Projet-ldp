#include "Score.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

ScoreManager::ScoreManager(const std::string& file, unsigned int score, unsigned int highscore) : 
filename_{file}, score_{score}, highscore_(highscore) {
    loadHighscore(); // charge et met a jour le highscore pendant l'initialisation à partir du fichier
}

ScoreManager::~ScoreManager() {
    saveHighscore(); // sauvegarde dans le file le highscore actuel a la fin de la partie
}

void ScoreManager::loadHighscore() {
    std::ifstream infile(filename_);
    if (infile) {
        infile >> highscore_;   
    } else {
        std::cerr << "Highscore file not found.\n";
    }
}

void ScoreManager::saveHighscore() {
    std::ofstream outfile(filename_);
    if (outfile) {
        outfile << highscore_;
    } else {
        std::cerr << "Failed to save highscore in file.\n";
    }
}

void ScoreManager::updateScore(std::vector<std::pair<ALLEGRO_COLOR, int>> colorScores, const ALLEGRO_COLOR& blockColor){
    bool colorFound = false;
    for (const auto& pair : colorScores){
        if(memcmp(&pair.first, &blockColor, sizeof(ALLEGRO_COLOR))==0){ 
            // verifie la bonne couleur et evite les copies inutiles
            colorFound = true;
            score_ += pair.second;
            break; // couleur a été trouvé
        }
    if(!colorFound){
        score_ += 10; // si couleur pas trouvé on ajoute par défaut
    }
    if(score_ > highscore_){
        setHighscore(score_); 
    }
    }
}

unsigned int ScoreManager::getHighscore(){
    return highscore_;
}

unsigned int ScoreManager::getScore(){
    return score_;
}

void ScoreManager::setHighscore(unsigned int newScore){
    highscore_ = newScore;
}
