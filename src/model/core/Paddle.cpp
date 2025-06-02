#include "Paddle.hpp"
#include <allegro5/allegro_primitives.h>
#include "algorithm"

#include "Laser.hpp"



Paddle::Paddle(Point center, float speed, Size size,
               ALLEGRO_COLOR frameColor, ALLEGRO_COLOR fillColor, bool laser_mode)
    : center_{ center }, speed_{speed}, size_{size},
      frameColor_{frameColor}, fillColor_{fillColor}, laser_mode_{laser_mode} {}


//void Paddle::update_position(int direction){
    // direction 1 vers la droite
    // direction -1 vers la gauche
   // center_.x += direction * speed_; 
//}


void Paddle::draw() {
    float x1 = center_.x - size_.width / 2;  // center - rayon = bord gauche
    float y1 = center_.y - size_.height / 2;  // bord bas 
    float x2 = center_.x + size_.width / 2;  // bord droit 
    float y2 = center_.y + size_.height / 2;  // bord haut

    al_draw_filled_rectangle(x1, y1, x2, y2, fillColor_);

    al_draw_rectangle(x1, y1, x2, y2, frameColor_, 1);
}

void Paddle::moveLeft(float delta, float boundary_left) {
    center_.x = std::max(center_.x - speed_ * delta, boundary_left + size_.width / 2);

}

void Paddle::moveRight(float delta, float boundary_right) {
    center_.x = std::min(center_.x + speed_ * delta, boundary_right - size_.width / 2);
}

bool Paddle::isLaserModeEnabled() const{
    return laser_mode_;
}

void Paddle::enableLaserMode() {
    laser_mode_ = true;
}
void Paddle::shootLaser(std::vector<Laser> &lasers) {
    if (laser_mode_) {
        float x = center_.x + size_.width / 2; // Position centrale de la raquette
        float y = center_.y;
        lasers.emplace_back(x, y, 400, COLOR_RED); // Vitesse et couleur du laser
    }
}