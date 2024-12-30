#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include "Block.h"

class Level {
public:
    // Constructor to initialize level properties
    Level(float screen_width, float screen_height, float rows, float cols, float block_width, float block_height, float spacing_x, float spacing_y);

    // Generate blocks for the level
    void generate_blocks();

    // Set a new level configuration
    void set_level(size_t new_rows, size_t new_cols);

    // Get a reference to the current blocks
    const std::vector<std::shared_ptr<Block>>& get_blocks() const;

    // Draw the blocks to the screen
    void draw_blocks() const;

    void reset_blocks();
private:
    float screen_width_;   // Screen width
    float screen_height_;  // Screen height
    float rows_;          // Number of rows of blocks
    float cols_;          // Number of columns of blocks
    float block_width_;    // Width of each block
    float block_height_;   // Height of each block
    float spacing_x_;      // Horizontal spacing between blocks
    float spacing_y_;      // Vertical spacing between blocks

    std::vector<std::shared_ptr<Block>> blocks_; // List of all blocks
};

#endif // LEVEL_H
