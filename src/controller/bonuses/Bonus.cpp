#include "Bonus.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"
#include "BonusLaser.hpp"
#include "../../model/game/Level.hpp"

Bonus::Bonus() 
    : type_('?'), visible_(true), active_(false), color_(COLOR_YELLOW)  {} // par defaut

