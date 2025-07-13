#include "Score.hpp"
#include "Block.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "../../utils/Color.hpp"

ScoreManager::ScoreManager(const std::string& file, unsigned int score, unsigned int highscore) : 
highscoreFile_{file}, score_{score}, highscore_(highscore) {

    score_rules_[COLOR_WHITE]   = 50;
    score_rules_[COLOR_ORANGE]  = 60;
    score_rules_[COLOR_CYAN]    = 70;
    score_rules_[COLOR_GREEN]   = 80;
    score_rules_[COLOR_RED]     = 90;
    score_rules_[COLOR_BLUE]    = 100;
    score_rules_[COLOR_MAGENTA] = 110;
    score_rules_[COLOR_YELLOW]  = 120;

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

void ScoreManager::updateScore(std::vector<std::pair<ALLEGRO_COLOR,
 int>>& colorScores, const ALLEGRO_COLOR& blockColor, std::shared_ptr<Block>& block){

    for (auto it = colorScores.begin(); it != colorScores.end(); ++it){
            if (std::next(it) == colorScores.end()) {
                break; // Stop before the last element
            }
            const auto& pair = *it;
            if(memcmp(&pair.first, &blockColor, sizeof(ALLEGRO_COLOR))==0){
                // verifie la bonne couleur et evite les copies inutiles
                score_+= pair.second;
                break;
            }
            if(memcmp(&colorScores[9].first, &blockColor, sizeof(ALLEGRO_COLOR))==0) {
                block->incrementHits();
                if (block->getHits() == 2) {
                    score_ += 200;
                    break;
                    }
                break;
            }
            else{
                score_ += 1; // block defaut
            }
    if(score_ > highscore_){
        setHighscore(score_); 
    }
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