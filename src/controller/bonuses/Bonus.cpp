#include "Bonus.hpp"
#include "../../model/Paddle.hpp"
#include "../../model/Ball.hpp"
#include "BonusLaser.hpp"
#include "../../model/game/Level.hpp"

Bonus::Bonus() 
    : type_('?'), color_(COLOR_YELLOW), visible_(true), active_(false)  {} // par defaut

