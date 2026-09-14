//
// Created by natha on 9/7/2026.
//

#include "States/State.h"
#include "Logic/Model.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
#include "Logic/ButtonModel.h"
#include "Window/Camera.h"

State::State(StateFactory::Key key, EngineContext& ctx, bool updating, bool listening, bool showing):
ctx(ctx),
listening(listening),
showing(showing),
updating(updating)
{
    std::pair<float, float> worldSize = getCtx().camera.getWorldDimensions();
    PolygonViewConfig config;
    config.fillColor = sf::Color(50, 50, 50);
    addModel(ModelFactory::createModel(getCtx(), {0,0}, worldSize, config));
}

//----------------------------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------------------------
void State::activate() {
    updating = true;
}
void State::deactivate() {
    updating = false;
}

void State::show() {
    showing = true;
}

void State::hide() {
    showing = false;
}

void State::attachInput() {
    listening = true;
}

void State::detachInput() {
    listening = false;
}

void State::addModel(std::unique_ptr<Model> model) {
    models.push_back(std::move(model));
}


//----------------------------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------------------------
const std::vector<std::unique_ptr<Model>>& State::getModels() const {return models;}
EngineContext &State::getCtx() {return ctx;}
bool State::isActive() const {return updating;}
bool State::isShowing() const {return showing;}
bool State::isAttachedToInput() const {return listening;}

//----------------------------------------------------------------------------------------------------------------------
//Logic
//----------------------------------------------------------------------------------------------------------------------
void State::update() {
    if (!updating) {return;}
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

void State::draw() {
    if (!showing) {return;}

    for (auto const& model : models) {
        model->drawView();
    }
}


