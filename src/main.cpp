#include "ArkanoidGame.hpp"

#include <iostream>

int main() {
    std::cout << "[DEBUG] main.cpp: Program started" << std::endl;

    ArkanoidGame game;
    game.run();

    return 0;
}