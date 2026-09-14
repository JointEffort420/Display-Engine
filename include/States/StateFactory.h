//
// Created by natha on 9/7/2026.
//

#ifndef DISPLAYENGINE_STATEFACTORY_H
#define DISPLAYENGINE_STATEFACTORY_H

#include <memory>
#include <type_traits>
#include <utility>

#include "Core/EngineContext.h"

namespace eng {
    class State;

    // Sole responsibility: construct States. Templated for the same reason as
    // ModelFactory::createGrid — State is the caller-chosen concrete type
    // (MenuState, ConwayState, ...), not something this factory hardcodes.
    class StateFactory {
    public:
        StateFactory() = default;

        class Key {
            friend class StateFactory;
        private:
            Key() = default;
        };

        template<typename StateT, typename... Args>
        static std::unique_ptr<StateT> createState(EngineContext& ctx, Args&&... args) {
            static_assert(std::is_base_of_v<State, StateT>, "StateT must derive from State");
            auto state = std::make_unique<StateT>(Key(), ctx, std::forward<Args>(args)...);
            state->onEnter();
            return state;
        }
    };
}

#endif //DISPLAYENGINE_STATEFACTORY_H