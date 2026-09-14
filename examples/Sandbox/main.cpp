//
// Created by natha on 9/13/2026.
//

#include <iostream>
#include <ostream>

#include <Controller/Space.h>

int main() {
    std::cout << "Sandbox initiated" << std::endl;
    Space space = Space();
    space.start();
}
