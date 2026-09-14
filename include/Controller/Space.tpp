#ifndef DISPLAYENGINE_SPACE_TPP
#define DISPLAYENGINE_SPACE_TPP

#include <utility>

#include "States/StateFactory.h"

class Space;

template<typename StateT, typename... Args>
void Space::start(Args&&... args)
{
    pushState<StateT>(
        std::forward<Args>(args)...
    );
}

template<typename StateT, typename... Args>
void Space::pushState(Args&&... args)
{
    stateManager->pushState(
        StateFactory::createState<StateT>(
            *ctx,
            std::forward<Args>(args)...
        )
    );
}

#endif