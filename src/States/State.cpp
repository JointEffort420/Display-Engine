//
// Created by natha on 9/7/2026.
//

#include "States/State.h"

#include "Logic/Model.h"
#include "States/StateManager.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
#include "Logic/ButtonModel.h"

State::State(StateFactory::Key key, EngineContext& ctx): ctx(ctx) {
    TextViewConfig config;
    config.string = "default state";
    models.push_back(ModelFactory::createModel(ctx, {0.5,0.05},  {1, 0.2}, config, Anchor::Center));
}

//----------------------------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------------------------
void State::activate() {
    active = true;
    Input::GetInstance()->attach(this);
}
void State::deactivate() {
    active = false;
    Input::GetInstance()->detach(this);
}

//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------
EngineContext &State::getCtx() {return ctx;}
bool State::isActive() const {return active;}

//----------------------------------------------------------------------------------------------------------------------
//Logic
//----------------------------------------------------------------------------------------------------------------------
void State::update() {
    updateModels();
    updateViews();
}
void State::updateModels() {
    for (auto& model : models) {
        model->update();
    }
}
void State::updateViews() {
    for (auto& model : models) {
        model->updateView();
    }
}
void State::nextState(std::unique_ptr<State> state) {
    ctx.stateManager.pushState(std::move(state));
}


void State::draw() {
    for (auto const& model : models) {
        model->drawView();
    }
}


