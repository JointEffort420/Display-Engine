//
// Created by natha on 9/7/2026.
//

#include "States/StateManager.h"
#include "States/State.h"

#include <iostream>

namespace eng {
    StateManager::StateManager(): IInputObserver() {
        Input::GetInstance()->attach(this);
    }

    StateManager::~StateManager() {
        Input::GetInstance()->detach(this);
    }
    //----------------------------------------------------------------------------------------------------------------------
    // Getters
    //----------------------------------------------------------------------------------------------------------------------
    bool StateManager::isEmpty() const {return stateStack.empty();}
    std::size_t StateManager::depth() const {return stateStack.size();}

    State& StateManager::topState()
    {
        if (stateStack.empty())
        {
            throw std::logic_error(
                "StateManager::topState() called on empty stack"
            );
        }

        return *stateStack.back();
    }

    const std::vector<std::unique_ptr<State>>& StateManager::getStates() const {
        return stateStack;
    }

    //----------------------------------------------------------------------------------------------------------------------
    // State management
    //----------------------------------------------------------------------------------------------------------------------

    void StateManager::pushState(std::unique_ptr<State> state)
    {
        if (!state)
        {
            std::cerr
                << "StateManager::pushState() called with nullptr — ignored"
                << std::endl;

            return;
        }

        stateStack.push_back(std::move(state));
    }

    void StateManager::requestPush(std::unique_ptr<State> state) {
        pendingTransitions.push_back({PendingTransition::Type::Push, std::move(state)});
    }

    void StateManager::popState()
    {
        if (stateStack.empty())
        {
            std::cerr
                << "StateManager::popState() called on an empty stack — ignored"
                << std::endl;

            return;
        }

        if (stateStack.size() == 1)
        {
            std::cerr
                << "StateManager::popState() refused: "
                   "cannot pop the last remaining state"
                << std::endl;

            return;
        }

        stateStack.back()->deactivate();
        stateStack.back()->hide();
        stateStack.back()->detachInput();
        stateStack.back()->onExit();

        stateStack.pop_back();
    }

    void StateManager::requestPop() {
        pendingTransitions.push_back({PendingTransition::Type::Push, nullptr});
    }

    void StateManager::applyPendingTransitions() {
        //Here the entries in 'pendingTransitions' get applied
        while (!pendingTransitions.empty()) {
            std::vector<PendingTransition> batch = std::move(pendingTransitions);
            pendingTransitions.clear();
            for (auto& entry : batch) {
                if (entry.type == PendingTransition::Type::Push) {
                    pushState(std::move(entry.state));
                }else if (entry.type == PendingTransition::Type::Pop) {
                    popState();
                }else {
                    std::cerr << "StateManager::applyPendingTransitions: Unexpected transition request" << std::endl;
                }
            }
        }
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Logic
    //----------------------------------------------------------------------------------------------------------------------
    void StateManager::update() {
        if (stateStack.empty()) {return;}
        for (auto& state : stateStack) {state->update();}
        applyPendingTransitions(); //Only after iterator-logic. Prevents UB
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Input
    //----------------------------------------------------------------------------------------------------------------------
    bool StateManager::onLeftPressed(
        const std::pair<unsigned int, unsigned int>& coordinates
    )
    {
        for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
        {
            State& state = **it;

            if (!state.isAttachedToInput())
            {
                continue;
            }

            if (state.onLeftPressed(coordinates))
            {
                return true;
            }
        }

        return false;
    }

    bool StateManager::onLeftReleased(
        const std::pair<unsigned int, unsigned int>& coordinates
    )
    {
        for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
        {
            State& state = **it;

            if (!state.isAttachedToInput())
            {
                continue;
            }

            if (state.onLeftReleased(coordinates))
            {
                return true;
            }
        }

        return false;
    }

    bool StateManager::onMouseMoved(
        const std::pair<unsigned int, unsigned int>& coordinates
    )
    {
        for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
        {
            State& state = **it;

            if (!state.isAttachedToInput())
            {
                continue;
            }

            if (state.onMouseMoved(coordinates))
            {
                return true;
            }
        }

        return false;
    }

    void StateManager::onResize() {
        for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it) {
            State& state = **it;
            state.onResize();
        }
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Drawing
    //----------------------------------------------------------------------------------------------------------------------
    void StateManager::draw()
    {
        if (stateStack.empty())
        {
            return;
        }

        // Bottom -> top.
        //
        // This is important for overlays:
        //
        // GameState
        // PauseState
        //
        // GameState is drawn first, then PauseState over it.

        for (auto& state : stateStack)
        {
            state->draw();
        }
    }
}