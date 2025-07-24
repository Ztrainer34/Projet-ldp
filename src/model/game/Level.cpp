#include "Level.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <random>

/*Level::Level(float screen_width, float screen_height, float rows, float cols, float block_width, float block_height, float spacing_x, float spacing_y)
        : screen_width_(screen_width), screen_height_(screen_height), rows_(rows), cols_(cols),
          block_width_(block_width), block_height_(block_height),
          spacing_x_(spacing_x), spacing_y_(spacing_y) {}*/

Level::Level(Size screenSize, size_t rows, size_t cols, Size blockSize, float spacing_x, float spacing_y) :
    screenSize_{screenSize}, rows_{rows}, cols_{cols}, blockSize_{blockSize}, 
    spacing_x_(spacing_x), spacing_y_(spacing_y) {}

Level::Level(Size blockSize, Point startPos, Point spacing)
    : blockSize_(blockSize), 
      start_x_(startPos.getX()), 
      start_y_(startPos.getY()),
      spacing_x_(spacing.getX()), 
      spacing_y_(spacing.getY()) {}


void Level::generateBlocks(const std::vector<std::string>& layout) {
        blocks_.clear(); // vide les bloc du lvl précédent
        // Pour lier les caractères '1', '2', etc., à des propriétés
        std::map<char, std::pair<ALLEGRO_COLOR, int>> blockRules = {
            {'1', {COLOR_WHITE, 50}},    
            {'2', {COLOR_ORANGE, 60}},      
            {'3', {COLOR_CYAN, 70}},       
            {'4', {COLOR_GREEN, 80}},         
            {'5', {COLOR_RED, 90}},         
            {'6', {COLOR_BLUE, 100}},        
            {'7', {COLOR_MAGENTA, 110}},     
            {'8', {COLOR_YELLOW, 120}}       
        };    
        for (size_t j = 0; j < layout.size(); ++j) {
            for (size_t i = 0; i < layout[j].length(); ++i) {
                
                char blockType = layout[j][i];
                if (blockType == '-') continue; // On ignore les espaces vides

                Point pos(start_x_ + i * (blockSize_.getWidth() + spacing_x_),
                        start_y_ + j * (blockSize_.getHeight() + spacing_y_));
                
                switch (blockType) {
                    case 'G':
                        blocks_.push_back(std::make_shared<GoldBlock>(pos, blockSize_, true));
                        break;
                    case 'S':
                        blocks_.push_back(std::make_shared<SilverBlock>(pos, blockSize_, true));
                        break;
                    default:
                        // Pour les briques standard de '1' à '8'
                        if (blockRules.count(blockType)) {
                            auto rule = blockRules.at(blockType);
                            ALLEGRO_COLOR color = rule.first;
                            int score = rule.second;
                            blocks_.push_back(std::make_shared<Block>(pos, blockSize_, true, color, 1, score));
                        }
                        break;
                }
            }
        }    
}


void Level::resetBlocks() {
    blocks_.clear();     // Clear all existing blocks
    generateBlocks(level1_layout);   // Regenerate blocks
}