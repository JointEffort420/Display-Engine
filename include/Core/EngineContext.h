#ifndef GAMEOFLIFE_ENGINECONTEXT_H
#define GAMEOFLIFE_ENGINECONTEXT_H

class Window;
class Camera;
class StateManager;
class Factory;

struct EngineContext {
    Window& window;
    Camera& camera;
    StateManager& stateManager;
    Factory& factory;

    EngineContext(Window& win, Camera& cam, StateManager& sm, Factory& fac)
        : window(win), camera(cam), stateManager(sm), factory(fac) {}
};

#endif //GAMEOFLIFE_ENGINECONTEXT_H