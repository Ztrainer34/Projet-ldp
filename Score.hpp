#ifndef SCORE_HPP
#define SCORE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Block.hpp"


class ScoreManager {
private:
    unsigned int score_ = 0;
    unsigned int highscore_ = 0;
    std::string filename_;

public:
    ScoreManager(const std::string& file, unsigned int score, unsigned int highscore);
    ~ScoreManager();

    void loadHighscore(); // preserve le highscore entre plusieurs partie
    void saveHighscore();
    void updateScore(std::vector<std::pair<ALLEGRO_COLOR, int>> colorScores, const ALLEGRO_COLOR& blockColor);
    unsigned int getHighscore();
    unsigned int getScore();
    void setHighscore(unsigned int newScore);

};

#endif //SCORE_HPP
