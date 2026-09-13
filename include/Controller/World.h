//
// Created by natha on 22/11/2025.
//

#ifndef GOL_GAME_H
#define GOL_GAME_H

//Libraries
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>


#include "../Representation/include/Window.h"
#include "../Representation/include/Camera.h"
#include "../States/include/StateManager.h"
#include "../Logic/include/Factory.h"

#include "../Utils/EngineContext.h"

class Game {
private:
    // Core owned subsystems
    std::unique_ptr<Window> window;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<StateManager> stateManager;
    std::unique_ptr<Factory> factory;

    // Context bundle referencing subsystems
    std::unique_ptr<EngineContext> ctx;

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    explicit Game();
    ~Game() = default;

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------
    void start();
    void stop();
    void run();

    //----------------------------------------------------------------------------------------------------------------------
    //View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------
};


#endif //GOL_GAME_H