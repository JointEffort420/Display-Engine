#include "Controller/Space.h"
#include "Input/Input.h"

Space::Space(
    const std::string& title,
    const std::pair<float, float>& worldSize,
    const std::pair<unsigned int, unsigned int>& windowSize
){
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

    clock = std::make_unique<Clock>();

    ctx = std::make_unique<EngineContext>(
        *window,
        *camera,
        *stateManager,
        *clock
    );
}

void Space::run() {
    running = true;
    while (window->isOpen()) {
        clock->update();
        window->clear();
        window->handleEvents(
            *Input::GetInstance(),
            *camera
        );
        stateManager->update();
        draw();
    }
}

void Space::draw() {
    stateManager->draw();
    window->display();
}


void Space::popState() {stateManager->popState();}

//----------------------------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------------------------
void Space::pause() {
    running = false;
}
void Space::resume() {
    running = true;
}

//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------
const State& Space::getTopState() const {return ctx->stateManager.topState();}
const std::vector<std::unique_ptr<State>>& Space::getStates() const {return ctx->stateManager.getStates();}
std::pair<float, float> Space::getSpaceSize(){return ctx->camera.getWorldDimensions();}
float Space::getSpaceWidth(){return ctx->camera.getWorldDimensions().first;}
float Space::getSpaceHeight(){return ctx->camera.getWorldDimensions().second;}