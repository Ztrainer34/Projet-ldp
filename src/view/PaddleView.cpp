#include "PaddleView.hpp"

void PaddleView::draw() {
    float x1 = paddle.getX() - paddle.getWidth() / 2;  // left edge
    float y1 = paddle.getY() - paddle.getHeight() / 2; // top edge
    float x2 = paddle.getX() + paddle.getWidth() / 2;  // right edge
    float y2 = paddle.getY() + paddle.getHeight() / 2; // bottom edge

    al_draw_filled_rectangle(x1, y1, x2, y2, getFillColor());
    al_draw_rectangle(x1, y1, x2, y2, getFrameColor(), 1);
}
