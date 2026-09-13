#include "Game.h"

Game::Game() {
    std::pair<unsigned int, unsigned int> windowSize = std::make_pair(800, 600);
    
    // 1. Construct base subsystems
    this->window = std::make_unique<Window>(windowSize.first, windowSize.second, "Game of Life");
    this->camera = std::make_unique<Camera>(windowSize);
    this->factory = std::make_unique<Factory>();
    this->stateManager = std::make_unique<StateManager>();

    // 2. Bind context referencing all components
    this->ctx = std::make_unique<EngineContext>(*window, *camera, *stateManager, *factory);

    // 3. Hand context over to state manager
    this->stateManager->setContext(*ctx);
}

void Game::start() {
    this->window->open();
    // Push initial state into manager
    this->stateManager->pushState(StateType::MenuStateType);
    this->run();
}

void Game::run() {
    while (window->isOpen()) {
        window->clear();
        stateManager->update();
        window->display();
    }

    stop();
}

void Game::stop() {
    // Cleanup if necessary
}