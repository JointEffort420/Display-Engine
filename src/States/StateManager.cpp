//
// Created by natha on 9/7/2026.
//

#include "States/StateManager.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
//Setter
//----------------------------------------------------------------------------------------------------------------------
void StateManager::setContext(EngineContext& cx) {ctx = &cx;}


//----------------------------------------------------------------------------------------------------------------------
//Logic
//----------------------------------------------------------------------------------------------------------------------
void StateManager::update() {
    if (!stateStack.empty()) {
        stateStack.top()->update();
    }
}

void StateManager::popState() {
    if (!stateStack.empty()) {
        stateStack.pop();
    }
    topState().activate();
}
State &StateManager::topState() {
    if (!stateStack.empty()) {
        return *stateStack.top();
    }
    std::cout << "Requesting top state of empty stack in stateManager" << std::endl;
}

void StateManager::pushState(std::unique_ptr<State> state) {
    if (!stateStack.empty()) { topState().deactivate(); }
    stateStack.push(std::move(state));   // <- use what was passed in
    stateStack.top()->activate();
}

//----------------------------------------------------------------------------------------------------------------------
//Draw, print & debug
//----------------------------------------------------------------------------------------------------------------------
void StateManager::draw() {
    topState().draw();
}