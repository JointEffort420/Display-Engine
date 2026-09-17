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
    class Scene;

    class SceneManager : public IInputObserver {
    private:
        // The vector is used as a stack
        std::vector<std::unique_ptr<Scene>> stateStack;

        //All transitions will pass through this request-form first.
        //This prevents undevined behaviour when iterating over stateStack
        struct PendingTransition {
            enum class Type {Push, Pop} type;
            std::unique_ptr<Scene> state;
        };
        std::vector<PendingTransition> pendingTransitions;
        void applyPendingTransitions();

    public:
        //------------------------------------------------------------------------------------------------------------------
        // Constructors & Destructor
        //------------------------------------------------------------------------------------------------------------------
        explicit SceneManager();
        ~SceneManager() override;

        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(const SceneManager&) = delete;

        SceneManager(SceneManager&&) = default;
        SceneManager& operator=(SceneManager&&) = default;

        //------------------------------------------------------------------------------------------------------------------
        // Getters
        //------------------------------------------------------------------------------------------------------------------

        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] std::size_t depth() const;
        [[nodiscard]] Scene& topState();
        [[nodiscard]] const std::vector<std::unique_ptr<Scene>>& getStates() const;

        //------------------------------------------------------------------------------------------------------------------
        // State management
        //------------------------------------------------------------------------------------------------------------------
        void pushState(std::unique_ptr<Scene> state);
        void requestPush(std::unique_ptr<Scene> state);
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