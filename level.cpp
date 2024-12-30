#include <vector>
#include <memory>
#include "Block.h"
#include "level.h"
#include "color.h"

#include <random>

    Level::Level(float screen_width, float screen_height, float rows, float cols, float block_width, float block_height, float spacing_x, float spacing_y)
        : screen_width_(screen_width), screen_height_(screen_height), rows_(rows), cols_(cols),
          block_width_(block_width), block_height_(block_height),
          spacing_x_(spacing_x), spacing_y_(spacing_y) {}

void Level::generate_blocks() {
        // Réinitialiser les blocs existants

        const float start_x = 50; // Position initiale en X
        const float start_y = 50; // Position initiale en Y

        std::random_device rd;
        std::mt19937 gen(rd());  // Mersenne Twister random number engine

        // Define a uniform distribution in the range [1, 100]
        std::uniform_int_distribution<> distrib(1, 100);

        // Generate and print a random number in the range [1, 100]

        const std::vector<ALLEGRO_COLOR> colors = {
            COLOR_WHITE, COLOR_ORANGE, COLOR_CYAN,
            COLOR_GREEN, COLOR_RED, COLOR_BLUE,
            COLOR_MAGENTA, COLOR_YELLOW
        };



        for (float i = 0; i < cols_; ++i) {
            for (float j = 0; j < rows_; ++j) {
                float x = start_x + i * (block_width_ + spacing_x_);
                float y = start_y + j * (block_height_ + spacing_y_);

                // Choisir une couleur aléatoire
                int random_number = distrib(gen);

                // Créer un bloc avec la couleur aléatoire
                blocks_.push_back(std::make_shared<Block>(x, y, block_width_, block_height_, COLOR_BLUE, COLOR_RED));
            }
        }
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


