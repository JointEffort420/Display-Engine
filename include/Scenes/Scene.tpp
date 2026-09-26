#ifndef DISPLAYENGINE_STATE_TPP
#define DISPLAYENGINE_STATE_TPP

#include <utility>
#include "Scenes/SceneManager.h"

namespace eng {
    class Scene;

    template<typename SceneT, typename... Args>
    void Scene::sceneTransition(Args&&... args) {
        ctx.stateManager.requestPush(SceneFactory::createScene<SceneT>( std::forward<Args>(args)...));
    }
}

#endif