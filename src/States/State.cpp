//
// Created by natha on 9/7/2026.
//

#include "States/State.h"
#include "Logic/Model.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
#include "Logic/ButtonModel.h"
#include "SFML/System/Time.hpp"
#include "Time/Clock.h"
#include "Window/Camera.h"

namespace eng {
    State::State(StateFactory::Key key, EngineContext& ctx, bool updating, bool listening, bool showing):
    ctx(ctx),
    listening(listening),
    showing(showing),
    updating(updating),
    timers(std::make_unique<TimerManager>())
    {
        PolygonViewConfig config;
        config.fillColor = sf::Color(10, 10, 10);
        addModel({0,0}, getSpaceSize(), config);
    }

    //----------------------------------------------------------------------------------------------------------------------
    //Timers
    //----------------------------------------------------------------------------------------------------------------------
    void State::after(float duration, std::function<void()> callback){
        timers->addTimer(duration, std::move(callback), false);
    }
    void State::every(float interval, std::function<void()> callback){
        timers->addTimer(interval, std::move(callback), true);
    }

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------
    void State::onExit() {
        models.clear();

        listening = false;
        showing = false;
        updating = false;
    }

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

    void State::addModel(const std::pair<float, float>& position, const std::pair<float, float>& size, const ViewConfig& config, Anchor anchor) {
        models.push_back(ModelFactory::createModel(ctx, position, size, config, anchor));
    }


    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------
    std::pair<float, float> State::getSpaceSize() const {return ctx.camera.getWorldDimensions();}
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
        timers->update(getCtx().clock.getDeltaTime());
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

    void State::onResize() {
        for (std::unique_ptr<Model>& model : models) {
            model->calibrateView();
        }
    }

    void State::draw() {
        if (!showing) {return;}

        for (auto const& model : models) {
            model->drawView();
        }
    }

    void State::reset() {
        onExit();
        onEnter();
    }
}
