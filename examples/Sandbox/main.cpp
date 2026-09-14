//
// Created by natha on 9/13/2026.
//

#include <iostream>
#include <ostream>

#include <Controller/Space.h>
#include "TestState.h"

int main() {
    std::cout << "Sandbox initiated" << std::endl;
    eng::Space space = eng::Space("Testwindow");
    space.start<TestState>();
    space.run();
}
