#include <vector>
#include "Drawable.cpp"
#include "Point.h"
#include "Size.h"
#include "Ball.cpp"
using namespace std;

class Block : public virtual Drawable {
    Point position_block;
    Size size_block;
    bool is_visible;
    const ALLEGRO_COLOR COLOR_GREY = al_map_rgb(200, 200, 200);

public:
    Block(float x, float y, float width, float height) :
        position_block{x, y}, size_block{width, height}, is_visible(true) {}

    void draw() override;

    // Handle collision with a ball
    void handleCollision(Ball& ball) {
        if (isColliding(ball)) {
            is_visible = false;
        }
    }

    // Check if the block and ball are colliding
    bool isColliding(const Ball& ball) {
        return ball.getPosition().x + ball.getRadius() > position_block.x && ball.getPosition().x - ball.getRadius()  < position_block.x + size_block.width &&
               ball.getPosition().y + ball.getRadius() > position_block.y && ball.getPosition().x - ball.getRadius()  < position_block.y + size_block.height;
    }

    // Getters and Setters for position_block
    Point getPosition() const {
        return position_block;
    }

    void setPosition(float x, float y) {
        position_block.x = x;
        position_block.y = y;
    }

    void setPosition(const Point& new_position) {
        position_block = new_position;
    }

    // Additional methods to access visibility and size
    bool getVisibility() const {
        return is_visible;
    }

    void setVisibility(bool visibility) {
        is_visible = visibility;
    }

    Size getSize() const {
        return size_block;
    }
};
