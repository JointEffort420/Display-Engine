#ifndef DISPLAYENGINE_STATE_TPP
#define DISPLAYENGINE_STATE_TPP

#include <utility>
#include "Scenes/SceneManager.h"

namespace eng {
    template<typename StateT, typename... Args>
    void Scene::stateTransition(Args&&... args) {
        ctx.stateManager.requestPush(SceneFactory::createState<StateT>(ctx, std::forward<Args>(args)...));
    }
}

#endif