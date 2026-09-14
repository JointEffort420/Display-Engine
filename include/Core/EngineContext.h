#ifndef DISPLAYENGINE_ENGINECONTEXT_H
#define DISPLAYENGINE_ENGINECONTEXT_H

class Window;
class Camera;
class StateManager;
class Clock;

struct EngineContext {
    Window& window;
    Camera& camera;
    StateManager& stateManager;
    Clock& clock;

    EngineContext(Window& win, Camera& cam, StateManager& sm, Clock& ck)
        : window(win), camera(cam), stateManager(sm), clock(ck) {}
};

#endif //DISPLAYENGINE_ENGINECONTEXT_H