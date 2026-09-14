//
// Created by natha on 9/7/2026.
//

#ifndef DISPLAYENGINE_STATE_H
#define DISPLAYENGINE_STATE_H

#include <functional>

#include "StateFactory.h"
#include "../Input/IInputObserver.h"
#include "Logic/ModelFactory.h"
#include "Logic/Model.h"
#include "Input/Input.h"
#include "Time/TimerManager.h"

namespace eng {
    class StateManager;

    class State {
    private:
        EngineContext& ctx;
        std::unique_ptr<TimerManager> timers;
        std::vector<std::unique_ptr<Model>> models;

        bool listening;//Determines wether state should be subscriber to input
        bool showing ;//Determines wether state is drawn
        bool updating ;//Determines wether state is updating

    protected:
        void after(float seconds, std::function<void()> callback);
        void every(float seconds, std::function<void()> callback);

    public:
        virtual ~State() = default;

        //----------------------------------------------------------------------------------------------------------------------
        //Constructors & Destructor
        //----------------------------------------------------------------------------------------------------------------------
        State() = delete;
        explicit State(StateFactory::Key key, EngineContext& ctx, bool updating = true, bool listening = true, bool showing = true);

        //----------------------------------------------------------------------------------------------------------------------
        //Setters
        //----------------------------------------------------------------------------------------------------------------------
        virtual void onEnter() = 0;
        virtual void onExit();

        void activate();
        void deactivate();
        void show();
        void hide();
        void attachInput();
        void detachInput();

        void addModel(std::unique_ptr<Model> model);
        void addModel(const std::pair<float, float>& position, const std::pair<float, float>& size, const ViewConfig& config, Anchor anchor = Anchor::TopLeft);

        //----------------------------------------------------------------------------------------------------------------------
        //Getters
        //----------------------------------------------------------------------------------------------------------------------
        [[nodiscard]] EngineContext& getCtx();
        [[nodiscard]] std::pair<float, float> getSpaceSize() const;
        [[nodiscard]] const std::vector<std::unique_ptr<Model>>& getModels() const;
        [[nodiscard]] bool isActive()const;
        [[nodiscard]] bool isShowing()const;
        [[nodiscard]] bool isAttachedToInput()const;

        //----------------------------------------------------------------------------------------------------------------------
        //Logic
        //----------------------------------------------------------------------------------------------------------------------
        virtual void update();
        virtual void updateModels();
        virtual void updateViews();
        void reset();

        template<typename StateT, typename... Args>
        void stateTransition(Args&&... args);

        //----------------------------------------------------------------------------------------------------------------------
        //Input (via StateManager)
        //----------------------------------------------------------------------------------------------------------------------
        virtual bool onLeftPressed(const std::pair<unsigned int, unsigned int> &windowCoordinates){return false;}
        virtual bool onLeftReleased(const std::pair<unsigned int, unsigned int> &windowCoordinates){return false;}
        virtual bool onMouseMoved(const std::pair<unsigned int, unsigned int> &windowCoordinates){return false;}
        virtual void onResize();

        //----------------------------------------------------------------------------------------------------------------------
        //Draw, print & debug
        //----------------------------------------------------------------------------------------------------------------------
        virtual void draw();
    };
}
#include "State.tpp"

#endif //DISPLAYENGINE_STATE_H