#ifndef DISPLAYENGINE_ENGINECONTEXT_H
#define DISPLAYENGINE_ENGINECONTEXT_H

namespace eng {
    class Window;
    class Camera;
    class SceneManager;
    class Clock;
    class FontManager;
    class TextureManager;

    struct EngineContext {
        Window& window;
        Camera& camera;
        SceneManager& stateManager;
        Clock& clock;
        FontManager& fontManager;
        TextureManager& textureManager;

        EngineContext(Window& win, Camera& cam, SceneManager& sm, Clock& ck, FontManager& fm, TextureManager& tm)
            : window(win), camera(cam), stateManager(sm), clock(ck), fontManager(fm), textureManager(tm) {}
    };
}

#endif //DISPLAYENGINE_ENGINECONTEXT_H