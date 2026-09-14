//
// Created by natha on 9/14/2026.
//

#include "Time/Clock.h"

#include <iostream>
#include <ostream>

Clock::Clock() {
    previousTime = ClockType::now();
    currentTime = previousTime;
    paused = false;
}

void Clock::update() {
    currentTime = ClockType::now();

    std::chrono::duration<float> rawDelta = currentTime - previousTime;
    previousTime = currentTime;

    if (paused) {
        deltaTime = 0.0f;
        return;
    } else {
        deltaTime = rawDelta.count() * timeScale;
        elapsedTime += deltaTime;
    }
}