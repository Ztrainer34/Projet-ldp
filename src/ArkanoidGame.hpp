#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include <vector>
#include <memory>
#include <cstdio>
#include <unordered_map>
#include "Laser.hpp"
#include "Block.hpp"
#include "Ball.hpp"
#include "Bonus.hpp"
#include "BonusCatch.hpp"
#include "BonusInterruption.hpp"
#include "BonusLaser.hpp"
#include "BonusSlow.hpp"
#include "Paddle.hpp"
#include "Capsule.hpp"
#include "Level.hpp"
#include "color.hpp"
#include "Score.hpp"
#include "setupAllegro.hpp"

#include <algorithm>
#include <iostream>

class ArkanoidGame{
    SetupAllegro setupAllegro;
};