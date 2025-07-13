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

class ScoreManager {
private:
    unsigned int score_ = 0;
    unsigned int highscore_ = 0;
    std::string highscoreFile_;
    std::vector<std::shared_ptr<Block>> blocks_; // List of all blocks
    std::map<ALLEGRO_COLOR, int, ColorComparator> score_rules_;  // colorcomp pour faciliter l'update et tri du score 

public:
    ScoreManager(const std::string& file, unsigned int score, unsigned int highscore);
    ~ScoreManager();

    void loadHighscore(); // preserve le highscore entre plusieurs partie
    void saveHighscore();
    void updateScore(std::vector<std::pair<ALLEGRO_COLOR, int>>& colorScores, const ALLEGRO_COLOR& blockColor,
    std::shared_ptr<Block>& block);
    unsigned int getHighscore() const;
    unsigned int getScore() const;
    void setHighscore(unsigned int newScore);

    std::vector<std::shared_ptr<Block>>& get_blocks() { return blocks_; }

};

#endif //SCORE_HPP