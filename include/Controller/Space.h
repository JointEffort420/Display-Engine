#ifndef DISPLAYENGINE_SPACE_H
#define DISPLAYENGINE_SPACE_H

#include <memory>

#include "Window/Window.h"
#include "Window/Camera.h"
#include "States/StateManager.h"
#include "Core/EngineContext.h"
#include "Window/DesktopData.h"
#include <States/State.h>

class Space
{
private:
    std::unique_ptr<Window> window;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<StateManager> stateManager;
    std::unique_ptr<EngineContext> ctx;

    void stop();
    void run();
    void draw();

public:
    Space() = delete;
    explicit Space(
        const std::string& title,
        const std::pair<float, float>& worldSize = {1, 1}
    );

    template<typename StateT, typename... Args>
    void start(Args&&... args);

    template<typename StateT, typename... Args>
    void pushState(Args&&... args);

    void popState();
};

#include "Space.tpp"

#endif