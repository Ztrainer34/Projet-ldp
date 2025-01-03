#include <vector>
#include <memory>
#include "Block.hpp"
#include "Level.hpp"
#include "color.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <random>

    Level::Level(float screen_width, float screen_height, float rows, float cols, float block_width, float block_height, float spacing_x, float spacing_y)
        : screen_width_(screen_width), screen_height_(screen_height), rows_(rows), cols_(cols),
          block_width_(block_width), block_height_(block_height),
          spacing_x_(spacing_x), spacing_y_(spacing_y) {}

void Level::generate_blocks(const std::string& file_path) {
        const float start_x = 50; // Position initiale en X
        const float start_y = 50; // Position initiale en Y



        const std::vector<ALLEGRO_COLOR> colors = {
            COLOR_WHITE, COLOR_ORANGE, COLOR_CYAN,
            COLOR_GREEN, COLOR_RED, COLOR_BLUE,
            COLOR_MAGENTA, COLOR_YELLOW,
            COLOR_GOLD, COLOR_SILVER,COLOR_WHITE, COLOR_ORANGE, COLOR_CYAN,
            COLOR_GREEN, COLOR_RED, COLOR_BLUE,
            COLOR_MAGENTA, COLOR_YELLOW,
            COLOR_GOLD, COLOR_SILVER, // Ajout des couleurs dorées et argentées
        };

        const std::vector<ALLEGRO_COLOR> colors_bonus = {
            COLOR_BLUE,COLOR_GREY,COLOR_GREEN
        };


        std::ifstream file("level1.txt");
        if (file_path == "base") {
            for (float i = 0; i < cols_; ++i) {
                for (float j = 0; j < rows_; ++j) {
                    float x = start_x + i * (block_width_ + spacing_x_);
                    float y = start_y + j * (block_height_ + spacing_y_);

                    // Choisir une couleur aléatoire

                    auto block = std::make_shared<Block>(x, y, block_width_, block_height_, COLOR_BLUE, colors[i], 1);

                    // Randomly assign a capsule to some blocks
                    if (rand() % 4 == 0) { // 25% of blocks get a capsule (you can tweak this logic)

                        ALLEGRO_COLOR random_color = colors_bonus[rand() % colors_bonus.size()];
                        auto capsule = std::make_shared<Capsule>(x + block_width_ / 2 - 10, y + block_height_ / 2, 20, 10, random_color);
                        block->setCapsule(capsule);
                    }

                    blocks_.push_back(block);





                }


            }
            return;
        }
        std::string line;
        if (file.is_open()) {
            while (std::getline(file, line)) {
                if (line.empty() || line[0] == '#') continue; // Ignore empty lines or comments

                std::istringstream iss(line);
                std::string value;
                float x, y, width, height;
                int color_index, border_color_index, hit_count;
                if (std::getline(iss, value, ',')) x = std::stof(value);
                if (std::getline(iss, value, ',')) y = std::stof(value);
                if (std::getline(iss, value, ',')) width = std::stof(value);
                if (std::getline(iss, value, ',')) height = std::stof(value);
                if (std::getline(iss, value, ',')) color_index = std::stoi(value);
                if (std::getline(iss, value, ',')) border_color_index = std::stoi(value);
                if (std::getline(iss, value, ',')) hit_count = std::stoi(value);

                // Extract values from the line
                if (iss >> x >> y >> width >> height >> color_index >> border_color_index >> hit_count) {
                    // Add the block to the list
                    blocks_.push_back(std::make_shared<Block>(x, y, width, height,
                        colors[color_index],
                        colors[border_color_index],'S')

                    );
                } else {
                    std::cerr << "Error: Could not parse line: " << line << std::endl;
                }
            }
        }
        file.close();
    }

    void Level::set_level(size_t new_rows, size_t new_cols) {
        rows_ = new_rows;
        cols_ = new_cols;
        generate_blocks();
    }

    const std::vector<std::shared_ptr<Block>>& Level::get_blocks() const {
        return blocks_;
    }

    void Level::draw_blocks() const {
        for (const auto& block : blocks_) {
            if (block->getVisibility()) {
                block->draw();
            }
        }
    }

void Level::reset_blocks() {
        blocks_.clear();     // Clear all existing blocks
        generate_blocks();   // Regenerate blocks
    }


