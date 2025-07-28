#include "Level.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <random>

#include "../../utils/Color.hpp"
#include "../../controller/bonuses/BonusType.hpp"
#include "../../controller/bonuses/BonusEnlarge.hpp"
#include "../../controller/bonuses/BonusCatch.hpp"
#include "../../controller/bonuses/BonusInterruption.hpp"
#include "../../controller/bonuses/BonusLaser.hpp"
#include "../../controller/bonuses/BonusSlow.hpp"
#include "../../controller/bonuses/BonusExtraLife.hpp"

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

    // A mettre dans Level.cpp, au début de generateBlocks
    std::map<BonusType, ALLEGRO_COLOR> bonus_rules = {
        {BonusType::ENLARGE, COLOR_BLUE},
        {BonusType::LASER, COLOR_PINK},
        {BonusType::EXTRA_LIFE, COLOR_GREY},
        {BonusType::CATCH, COLOR_GREEN},
        {BonusType::SLOW_BALL, COLOR_ORANGE},
        {BonusType::SPLIT, COLOR_YELLOW}
    };

    std::vector<ALLEGRO_COLOR> capsuleColors = {
        COLOR_RED, COLOR_GREY, COLOR_GREEN, COLOR_YELLOW, COLOR_BLACK, COLOR_WHITE, COLOR_ORANGE, COLOR_CYAN, COLOR_BLUE, COLOR_MAGENTA, COLOR_PINK, COLOR_GOLD, COLOR_SILVER
    };

    std::vector<BonusType> possibleBonuses = { BonusType::ENLARGE, BonusType::LASER,  BonusType::EXTRA_LIFE,  BonusType::CATCH,  BonusType::SLOW_BALL,  BonusType::SPLIT };
    std::uniform_int_distribution<> distribBonus(0, possibleBonuses.size() - 1);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> colorDis(0, capsuleColors.size() - 1);
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
                        auto block = std::make_shared<Block>(pos, blockSize_, true, color, 1, score);
                        // 20% chance to add a capsule
                        if (dis(gen) < 0.2) {
                            BonusType randomType = possibleBonuses[distribBonus(gen)];
                            std::shared_ptr<Bonus> bonus = nullptr;

                            switch (randomType) {
                            case BonusType::ENLARGE:
                                bonus = std::make_shared<BonusEnlarge>();
                                break;
                            case BonusType::LASER:
                                bonus = std::make_shared<BonusLaser>();
                                break;
                            case BonusType::CATCH:
                                bonus = std::make_shared<BonusCatch>();
                                break;
                            case BonusType::SLOW_BALL:
                                bonus = std::make_shared<BonusSlow>();
                                break;
                            case BonusType::SPLIT:
                                bonus = std::make_shared<BonusInterruption>();
                                break;
                            case BonusType::EXTRA_LIFE:
                                bonus = std::make_shared<BonusExtraLife>();
                                break;
                            
                            }
                            Size capsule_size(30, 15);
                            ALLEGRO_COLOR capsuleColor = bonus_rules.at(randomType);
                            auto capsule = std::make_shared<Capsule>(pos, capsule_size, true, capsuleColor, bonus);
                            block->setCapsule(capsule);
                        }
                        blocks_.push_back(block);
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

const std::vector<std::shared_ptr<Block>>& Level::get_blocks() const {
    return blocks_;
}