//
// Created by natha on 9/14/2026.
//

#ifndef DISPLAYENGINE_TIMER_H
#define DISPLAYENGINE_TIMER_H

#include <vector>
#include <functional>

namespace eng {
    class Timer {
    private:
        float duration{0.0f};
        float remaining{0.0f};
        bool expired{false};
        bool repeating{false};

        std::function<void()> callback;

    public:
        explicit Timer(float durationSeconds, bool isRepeating = false);
        explicit Timer(float durationSeconds, std::function<void()> onExpiredCallback, bool isRepeating = false);

        void update(float deltaTime);
        void reset();

        [[nodiscard]] bool isExpired() const { return expired; }
        [[nodiscard]] float getRemaining() const { return remaining; }
        [[nodiscard]] float getProgress() const { return duration > 0.0f ? (1.0f - (remaining / duration)) : 1.0f; }
    };
}

#endif //DISPLAYENGINE_TIMER_H