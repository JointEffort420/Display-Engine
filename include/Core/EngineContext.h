#ifndef DISPLAYENGINE_ENGINECONTEXT_H
#define DISPLAYENGINE_ENGINECONTEXT_H

namespace eng {
    class Window;
    class Camera;
    class SceneManager;
    class Clock;

    struct EngineContext {
        Window& window;
        Camera& camera;
        SceneManager& stateManager;
        Clock& clock;

        EngineContext(Window& win, Camera& cam, SceneManager& sm, Clock& ck)
            : window(win), camera(cam), stateManager(sm), clock(ck) {}
    };
}

#endif //DISPLAYENGINE_ENGINECONTEXT_H