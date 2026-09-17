//
// Created by natha on 9/7/2026.
//

#include "Scenes/Scene.h"
#include "Logic/Model.h"

//----------------------------------------------------------------------------------------------------------------------
//Constructors & Destructor
//----------------------------------------------------------------------------------------------------------------------
#include "Logic/ButtonModel.h"
#include "SFML/System/Time.hpp"
#include "Time/Clock.h"
#include "Window/Camera.h"

namespace eng {
    Scene::Scene(SceneFactory::Key key, EngineContext& ctx, bool updating, bool listening, bool showing):
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
    void Scene::after(float duration, std::function<void()> callback){
        timers->addTimer(duration, std::move(callback), false);
    }
    void Scene::every(float interval, std::function<void()> callback){
        timers->addTimer(interval, std::move(callback), true);
    }

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------
    void Scene::onExit() {
        models.clear();

        listening = false;
        showing = false;
        updating = false;
    }

    void Scene::activate() {
        updating = true;
    }
    void Scene::deactivate() {
        updating = false;
    }

    void Scene::show() {
        showing = true;
    }

    void Scene::hide() {
        showing = false;
    }

    void Scene::attachInput() {
        listening = true;
    }

    void Scene::detachInput() {
        listening = false;
    }

    void Scene::addModel(std::unique_ptr<Model> model) {
        models.push_back(std::move(model));
    }

    void Scene::addModel(const std::pair<float, float>& position, const std::pair<float, float>& size, const ViewConfig& config, Anchor anchor) {
        models.push_back(ModelFactory::createModel(ctx, position, size, config, anchor));
    }


    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------
    std::pair<float, float> Scene::getSpaceSize() const {return ctx.camera.getWorldDimensions();}
    const std::vector<std::unique_ptr<Model>>& Scene::getModels() const {return models;}
    EngineContext &Scene::getCtx() {return ctx;}
    bool Scene::isActive() const {return updating;}
    bool Scene::isShowing() const {return showing;}
    bool Scene::isAttachedToInput() const {return listening;}

    //----------------------------------------------------------------------------------------------------------------------
    //Logic
    //----------------------------------------------------------------------------------------------------------------------
    void Scene::update() {
        if (!updating) {return;}
        timers->update(getCtx().clock.getDeltaTime());
        updateModels();
        updateViews();
    }
    void Scene::updateModels() {
        for (auto& model : models) {
            model->update();
        }
    }
    void Scene::updateViews() {
        for (auto& model : models) {
            model->updateView();
        }
    }

    void Scene::onResize() {
        for (std::unique_ptr<Model>& model : models) {
            model->calibrateView();
        }
    }

    void Scene::draw() {
        if (!showing) {return;}

        for (auto const& model : models) {
            model->drawView();
        }
    }

    void Scene::reset() {
        onExit();
        onEnter();
    }
}
