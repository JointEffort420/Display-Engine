//
// Created by natha on 9/7/2026.
//

#include "../include/StateManager.h"

#include <iostream>
#include <ostream>

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

void StateManager::pushState(StateType stateType) {
    if (!ctx) {
        std::cerr << "stateManager::pushState(StateType " << stateType << ") before ctx was injected" << std::endl;
        return;
    }

    if (!stateStack.empty()) {topState().deactivate();}
    std::unique_ptr<State> newState = ctx->factory.createState(*ctx, stateType);
    if (newState) {
        stateStack.push(std::move(newState));
    }
}

//----------------------------------------------------------------------------------------------------------------------
//Draw, print & debug
//----------------------------------------------------------------------------------------------------------------------
void draw();
