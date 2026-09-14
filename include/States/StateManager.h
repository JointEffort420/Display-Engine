//
// Created by natha on 9/7/2026.
//

#ifndef DISPLAYENGINE_STATEMANAGER_H
#define DISPLAYENGINE_STATEMANAGER_H

#include <memory>
#include <vector>
#include <cstddef>
#include <stdexcept>

#include "../Input/IInputObserver.h"

namespace eng {
    class State;

    class StateManager : public IInputObserver {
    private:
        // The vector is used as a stack
        std::vector<std::unique_ptr<State>> stateStack;

        //All transitions will pass through this request-form first.
        //This prevents undevined behaviour when iterating over stateStack
        struct PendingTransition {
            enum class Type {Push, Pop} type;
            std::unique_ptr<State> state;
        };
        std::vector<PendingTransition> pendingTransitions;
        void applyPendingTransitions();

    public:
        //------------------------------------------------------------------------------------------------------------------
        // Constructors & Destructor
        //------------------------------------------------------------------------------------------------------------------
        explicit StateManager();
        ~StateManager() override;

        StateManager(const StateManager&) = delete;
        StateManager& operator=(const StateManager&) = delete;

        StateManager(StateManager&&) = default;
        StateManager& operator=(StateManager&&) = default;

        //------------------------------------------------------------------------------------------------------------------
        // Getters
        //------------------------------------------------------------------------------------------------------------------

        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] std::size_t depth() const;
        [[nodiscard]] State& topState();
        [[nodiscard]] const std::vector<std::unique_ptr<State>>& getStates() const;

        //------------------------------------------------------------------------------------------------------------------
        // State management
        //------------------------------------------------------------------------------------------------------------------
        void pushState(std::unique_ptr<State> state);
        void requestPush(std::unique_ptr<State> state);
        void popState();
        void requestPop();

        //------------------------------------------------------------------------------------------------------------------
        // Logic
        //------------------------------------------------------------------------------------------------------------------
        void update();

        //------------------------------------------------------------------------------------------------------------------
        // Input
        //------------------------------------------------------------------------------------------------------------------
        bool onLeftPressed(const std::pair<unsigned int, unsigned int> &windowCoordinates) override;
        bool onLeftReleased(const std::pair<unsigned int, unsigned int> &windowCoordinates) override;
        bool onMouseMoved(const std::pair<unsigned int, unsigned int> &windowCoordinates) override;
        void onResize() override;

        //------------------------------------------------------------------------------------------------------------------
        // Drawing
        //------------------------------------------------------------------------------------------------------------------

        void draw();
    };
}

#endif // DISPLAYENGINE_STATEMANAGER_H