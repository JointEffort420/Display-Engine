#ifndef DISPLAYENGINE_SPACE_TPP
#define DISPLAYENGINE_SPACE_TPP

#include <utility>

#include "States/StateFactory.h"

template<typename StateT, typename... Args>
void Space::start(Args&&... args)
{
    window->open();

    pushState<StateT>(
        std::forward<Args>(args)...
    );

    run();
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