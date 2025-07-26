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
    

public:
    ScoreManager(const std::string& file, unsigned int score, unsigned int highscore);
    ~ScoreManager();

    void loadHighscore(); // preserve le highscore entre plusieurs partie
    void saveHighscore();
    void updateScore(unsigned int pts);
    unsigned int getHighscore() const;
    unsigned int getScore() const;
    void setHighscore(unsigned int newScore);
    void resetScore(){ score_ = 0; }

    std::vector<std::shared_ptr<Block>>& get_blocks() { return blocks_; }

};

#endif //SCORE_HPP