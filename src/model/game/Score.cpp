#include "Score.hpp"
#include "../Block.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "../../utils/Color.hpp"

ScoreManager::ScoreManager(const std::string& file, unsigned int score, unsigned int highscore) : 
highscoreFile_{file}, score_{score}, highscore_(highscore) {
    loadHighscore(); // charge et met a jour le highscore pendant l'initialisation à partir du fichier
}

ScoreManager::~ScoreManager() {
    saveHighscore(); // sauvegarde dans le file le highscore actuel a la fin de la partie
}

void ScoreManager::loadHighscore() {
    std::ifstream infile(highscoreFile_);
    if (infile) {
        infile >> highscore_;   
    } else {
        std::cerr << "Highscore file not found.\n";
    }
}

void ScoreManager::saveHighscore() {
    std::ofstream outfile(highscoreFile_);
    if (outfile) {
        outfile << highscore_;
    } else {
        std::cerr << "Failed to save highscore in file.\n";
    }
}

void ScoreManager::updateScore(unsigned int pts){
    score_ += pts;
    if(score_ > highscore_){
        setHighscore(score_); 
    }
}

unsigned int ScoreManager::getHighscore() const{
    return highscore_;
}

unsigned int ScoreManager::getScore() const{
    return score_;
}

void ScoreManager::setHighscore(unsigned int newScore){
    highscore_ = newScore;
}