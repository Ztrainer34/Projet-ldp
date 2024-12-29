#include <vector>
#include <memory>
#include "Block.h"
#include "level.h"
#include "color.h"

    Level::Level(float screen_width, float screen_height, float rows, float cols, float block_width, float block_height, float spacing_x, float spacing_y)
        : screen_width_(screen_width), screen_height_(screen_height), rows_(rows), cols_(cols),
          block_width_(block_width), block_height_(block_height),
          spacing_x_(spacing_x), spacing_y_(spacing_y) {}

    void Level::generate_blocks() {
        blocks_.clear(); // Clear existing blocks



        std::vector<std::shared_ptr<Block>> blocks;
        const float start_x = 50;         // Position initiale en X
        const float start_y = 50;         // Position initiale en Y
        for (float i = 0; i < cols_; ++i) {
            for (float j = 0; j < rows_; ++j) {
                float x = start_x + i * (block_width_ + spacing_x_)-45;
                float y = start_y + j * (block_height_ + spacing_y_);
                blocks.push_back(std::make_shared<Block>(x, y, block_width_, block_height_, al_map_rgb(0, 0, 255), al_map_rgb(255, 0, 0)));
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


