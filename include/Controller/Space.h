//
// Created by natha on 22/11/2025.
//

#ifndef DISPLAYENGINE_WORLD_H
#define DISPLAYENGINE_WORLD_H

//Libraries
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>


#include "Window/Window.h"
#include "Window/Camera.h"
#include "States/StateManager.h"
#include "Core/EngineContext.h"

class Space {
private:
    // Core owned subsystems
    std::unique_ptr<Window> window;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<StateManager> stateManager;

    // Context bundle referencing subsystems
    std::unique_ptr<EngineContext> ctx;

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    explicit Space();
    ~Space() = default;

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------
    void start();
    void stop();
    void run();

    //----------------------------------------------------------------------------------------------------------------------
    //View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------
    void draw();
};


#endif //GOL_World_H