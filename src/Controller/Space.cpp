#include "Controller/Space.h"
#include "Input/Input.h"

Space::Space(
    const std::string& title,
    const std::pair<float, float>& worldSize
)
{
    const auto windowSize = getModestWindowSize(worldSize);

    window = std::make_unique<Window>(
        windowSize.first,
        windowSize.second,
        title
    );

    camera = std::make_unique<Camera>(
        worldSize,
        windowSize
    );

    stateManager = std::make_unique<StateManager>();

    ctx = std::make_unique<EngineContext>(
        *window,
        *camera,
        *stateManager
    );
}

void Space::run()
{
    while (window->isOpen())
    {
        window->clear();

        window->handleEvents(
            *Input::GetInstance(),
            *camera
        );

        stateManager->update();

        draw();
    }

    stop();
}

void Space::draw()
{
    stateManager->draw();
    window->display();
}

void Space::stop()
{
}

void Space::popState()
{
    stateManager->popState();
}