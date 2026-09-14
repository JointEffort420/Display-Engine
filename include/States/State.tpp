#ifndef DISPLAYENGINE_STATE_TPP
#define DISPLAYENGINE_STATE_TPP

#include <utility>
#include "States/StateManager.h"

template<typename StateT, typename... Args>
void State::stateTransition(Args&&... args) {
    ctx.stateManager.requestPush(StateFactory::createState<StateT>(ctx, std::forward<Args>(args)...));
}

#endif