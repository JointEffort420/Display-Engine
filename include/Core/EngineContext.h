#ifndef DISPLAYENGINE_ENGINECONTEXT_H
#define DISPLAYENGINE_ENGINECONTEXT_H

class Window;
class Camera;
class StateManager;
class ModelFactory;
class ViewFactory;

struct EngineContext {
    Window& window;
    Camera& camera;
    StateManager& stateManager;

    EngineContext(Window& win, Camera& cam, StateManager& sm)
        : window(win), camera(cam), stateManager(sm) {}
};

#endif //DISPLAYENGINE_ENGINECONTEXT_H