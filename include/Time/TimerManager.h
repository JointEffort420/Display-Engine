//
// Created by natha on 9/14/2026.
//

#ifndef DISPLAYENGINE_TIMERMANAGER_H
#define DISPLAYENGINE_TIMERMANAGER_H

#include <vector>
#include <memory>
#include <functional>
#include "Timer.h"

class TimerManager {
private:
    std::vector<std::unique_ptr<Timer>> timers;

public:
    TimerManager() = default;

    void addTimer(float durationSeconds, std::function<void()> callback, bool isRepeating = false);

    void update(float deltaTime);
    void clear();

    [[nodiscard]] std::size_t getActiveTimerCount() const { return timers.size(); }
};

#endif //DISPLAYENGINE_TIMERMANAGER_H