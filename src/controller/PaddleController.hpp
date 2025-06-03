#include <algorithm> // pour std::max/min

class PaddleController {
private:
    Paddle& paddle_;
    std::vector<Laser>& lasers_;
    float boundary_left_;
    float boundary_right_;

public:
    PaddleController(Paddle& p, std::vector<Laser>& l,
                     float left, float right)
      : paddle_(p), lasers_(l),
        boundary_left_(left), boundary_right_(right) {}

    // Appelé depuis la boucle de jeu
    void handleInput(const InputState& input, float deltaTime) {
        // Mouvement
        if (input.isKeyDown(Key::Left)) {
            auto pos = paddle_.getPosition();
            pos.x = std::max(boundary_left_,
                             pos.x - paddle_.getSpeed() * deltaTime);
            paddle_.setPosition(pos);
        }
        else if (input.isKeyDown(Key::Right)) {
            auto pos = paddle_.getPosition();
            pos.x = std::min(boundary_right_,
                             pos.x + paddle_.getSpeed() * deltaTime);
            paddle_.setPosition(pos);
        }

        // Bonus laser
        if (input.isKeyPressed(Key::Space) && paddle_.isLaserModeEnabled()) {
            lasers_.push_back(Laser(paddle_.getPosition()));
        }
    }

    // Activation externe du bonus
    void activateLaserBonus() {
        paddle_.setLaserMode(true);
    }
};
