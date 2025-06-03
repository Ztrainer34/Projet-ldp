#include <memory>
#include <vector>
#include "Drawable.hpp"

class GameView {
private:
    std::vector<std::unique_ptr<Drawable>> drawables;

public:
    void addRenderable(std::unique_ptr<Drawable> d) {
        drawables.push_back(std::move(d));
    }

    void renderAll() {
        for (auto& d : drawables) {
            d->draw();
        }
    }
};
