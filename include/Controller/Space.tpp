#ifndef DISPLAYENGINE_SPACE_TPP
#define DISPLAYENGINE_SPACE_TPP

#include <utility>

#include "Scenes/SceneFactory.h"

namespace eng {
    class Space;

    template<typename StateT, typename... Args>
    void Space::start(Args&&... args)
    {
        pushState<StateT>(
            std::forward<Args>(args)...
        );
    }

    template<typename SceneT, typename... Args>
    void Space::pushState(Args&&... args)
    {
        stateManager->pushState(
            SceneFactory::createScene<SceneT>(
                *ctx,
                std::forward<Args>(args)...
            )
        );
    }
}

#endif