//
// Created by natha on 9/7/2026.
//

#ifndef DISPLAYENGINE_STATE_H
#define DISPLAYENGINE_STATE_H

#include "StateFactory.h"
#include "Logic/IInputObserver.h"
#include "Window/Camera.h"
#include "Logic/ModelFactory.h"
#include "Logic/Model.h"

class StateManager;

class State : public IInputObserver{
private:
    EngineContext& ctx;

    std::vector<std::unique_ptr<Model>> models;

    bool active = true;

public:
    virtual ~State() = default;

    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    State() = delete;
    explicit State(StateFactory::Key key, EngineContext& ctx);

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------
    void activate();
    void deactivate();

    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------
    EngineContext& getCtx();
    [[nodiscard]] bool isActive()const;

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------
    virtual void update();
    virtual void updateModels();
    virtual void updateViews();
    virtual void nextState(std::unique_ptr<State> state);

    //----------------------------------------------------------------------------------------------------------------------
    //Subscriptions
    //----------------------------------------------------------------------------------------------------------------------
    void onLeftPressed(const std::pair<unsigned int, unsigned int> &windowCoordinates) override {}
    void onLeftReleased(const std::pair<unsigned int, unsigned int> &windowCoordinates) override {}
    void onMouseMoved(const std::pair<unsigned int, unsigned int> &windowCoordinates) override{}

    //----------------------------------------------------------------------------------------------------------------------
    //Draw, print & debug
    //----------------------------------------------------------------------------------------------------------------------
    virtual void draw();
};

#endif //DISPLAYENGINE_STATE_H