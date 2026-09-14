//
// Created by natha on 9/14/2026.
//

#ifndef DISPLAYENGINE_CLOCK_H
#define DISPLAYENGINE_CLOCK_H

#include <chrono>

namespace eng {
    class Clock {
    private:
        using ClockType = std::chrono::steady_clock;

        ClockType::time_point previousTime;
        ClockType::time_point currentTime;

        float deltaTime{0.0f};
        float elapsedTime{0.0f};

        float timeScale{1.0f};
        bool paused;

    public:
        Clock();

        void update();

        [[nodiscard]] float getDeltaTime() const { return deltaTime; }
        [[nodiscard]] float getElapsedTime() const { return elapsedTime; }

        void pause() { paused = true; }
        void resume() { paused = false; }
        [[nodiscard]] bool isPaused() const { return paused; }

        void setTimeScale(float scale) { timeScale = scale > 0.0f ? scale : 0.0f; }
        [[nodiscard]] float getTimeScale() const { return timeScale; }
    };
}

#endif //DISPLAYENGINE_CLOCK_H