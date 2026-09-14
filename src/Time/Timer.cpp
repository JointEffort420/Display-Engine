//
// Created by natha on 9/14/2026.
//

#include "Time/Timer.h"
#include <algorithm>

Timer::Timer(float durationSeconds, bool isRepeating)
    : duration(durationSeconds), remaining(durationSeconds), repeating(isRepeating) {}

Timer::Timer(float durationSeconds, std::function<void()> onExpiredCallback, bool isRepeating)
    : duration(durationSeconds), remaining(durationSeconds), repeating(isRepeating), callback(std::move(onExpiredCallback)) {}

void Timer::update(float deltaTime) {
    if (expired) return;

    remaining -= deltaTime;

    if (remaining <= 0.0f) {
        if (callback) callback();

        if (repeating) {
            remaining += duration; // Retain extra precision offset
        } else {
            remaining = 0.0f;
            expired = true;
        }
    }
}

void Timer::reset() {
    remaining = duration;
    expired = false;
}