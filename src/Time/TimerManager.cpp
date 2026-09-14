//
// Created by natha on 9/14/2026.
//

#include "Time/TimerManager.h"
#include <algorithm>
#include <stdexcept>

void TimerManager::addTimer(float durationSeconds, std::function<void()> callback, bool repeating){
    if (durationSeconds < 0.0f) throw std::invalid_argument("Timer duration cannot be negative.");
    if (!callback) throw std::invalid_argument("Timer callback cannot be empty.");


    auto timer = std::make_unique<Timer>(
        durationSeconds,
        std::move(callback),
        repeating
    );

    timers.push_back(std::move(timer));
}

void TimerManager::update(float deltaTime) {
    for (auto& timer : timers) {
        if (timer) {
            timer->update(deltaTime);
        }
    }

    timers.erase(
        std::remove_if(timers.begin(), timers.end(), [](const std::unique_ptr<Timer>& timer) {
            return !timer || timer->isExpired();
        }),
        timers.end()
    );
}

void TimerManager::clear() {
    timers.clear();
}