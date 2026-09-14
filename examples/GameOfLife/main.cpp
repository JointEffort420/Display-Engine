//
// Created by natha on 9/13/2026.
//

#include <iostream>
#include <ostream>

#include "MenuState.h"

int main() {
    std::cout << "Game of Life initiated" << std::endl;
    Space space = Space("Game of Life");
    space.start<MenuState>();
}