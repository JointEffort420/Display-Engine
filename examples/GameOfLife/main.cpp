//
// Created by natha on 9/13/2026.
//

#include <iostream>
#include <ostream>

#include "MenuScene.h"
#include "GridScene.h"

int main() {
    std::cout << "Game of Life initiated" << std::endl;
    eng::Space space = eng::Space("Game of Life");
    space.start<GridScene>();
    space.run();
}