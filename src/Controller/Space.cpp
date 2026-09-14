#include "Controller/Space.h"

#include "States/StateFactory.h"

Space::Space() {
    std::pair<unsigned int, unsigned int> windowSize = std::make_pair(800, 600);

    // 1. Construct base subsystems
    this->window = std::make_unique<Window>(windowSize.first, windowSize.second, "Game of Life");
    this->camera = std::make_unique<Camera>(windowSize);
    this->stateManager = std::make_unique<StateManager>();

    // 2. Bind context referencing all components
    this->ctx = std::make_unique<EngineContext>(*window, *camera, *stateManager);

    // 3. Hand context over to state manager
    this->stateManager->setContext(*ctx);
}

void Space::start() {
    window->open();
    // Push initial state into manager
    stateManager->pushState(StateFactory::createState<State>(*ctx));
    run();
}

void Space::run() {
    while (window->isOpen()) {
        window->clear();
        window->handleEvents(*Input::GetInstance(), *camera);
        stateManager->update();
        draw();
    }
    stop();
}

void Space::stop() {
    // Cleanup if necessary
}

void Space::draw() {
    stateManager->draw();
    window->display();
}