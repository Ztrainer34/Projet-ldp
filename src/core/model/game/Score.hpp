#ifndef SCORE_HPP
#define SCORE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <allegro5/allegro.h> #include <allegro5/allegro_color.h>


class Block;

class ScoreManager {
private:
    unsigned int score_ = 0;
    unsigned int highscore_ = 0;
    std::string filename_;
    std::vector<std::shared_ptr<Block>> blocks_; // List of all blocks

public:
    ScoreManager(const std::string& file, unsigned int score, unsigned int highscore);
    ~ScoreManager();

    void loadHighscore(); // preserve le highscore entre plusieurs partie
    void saveHighscore();
    void updateScore(std::vector<std::pair<ALLEGRO_COLOR, int>>& colorScores, const ALLEGRO_COLOR& blockColor,
    std::shared_ptr<Block>& block);
    unsigned int getHighscore();
    unsigned int getScore();
    void setHighscore(unsigned int newScore);

    std::vector<std::shared_ptr<Block>>& get_blocks() { return blocks_; }

};

#endif //SCORE_HPP