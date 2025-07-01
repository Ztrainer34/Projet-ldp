#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <memory>


#include "Point.hpp"
#include "Size.hpp"

class Block;
class Capsule;

class Level {
public:
    // Constructor to initialize level properties
    Level(Size screen_size, size_t rows, size_t cols, Size block_size, float spacing_x, float spacing_y);
    
    // Generate blocks for the level
    void generateBlocks(const std::string& file_path= "base");

    // Set a new level configuration
    void set_level(size_t new_rows, size_t new_cols);

    // Get a reference to the current blocks
    std::vector<std::shared_ptr<Block>>& getBlocks()  { return blocks_; }
    
    void reset_blocks();

    // Draw the blocks to the screen
    void draw_blocks() const;

     // Get a reference to the current blocks
    std::vector<std::shared_ptr<Capsule>> get_capsules() const {
        return capsules;
    }
     std::vector<std::shared_ptr<Block>>& get_blocks() { return blocks_; }



private:
    Size screen_size_;      // Screen size
    size_t rows_;           // Number of rows of blocks
    size_t cols_;           // Number of columns of blocks
    Size block_size_;       // Size of each block
    float spacing_x_;       // Horizontal spacing between blocks
    float spacing_y_;       // Vertical spacing between blocks
    std::vector<std::shared_ptr<Capsule>> capsules;
    std::vector<std::shared_ptr<Block>> blocks_; // List of all blocks
};

#endif // LEVEL_HPP
