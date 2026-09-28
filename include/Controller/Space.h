#ifndef DISPLAYENGINE_SPACE_H
#define DISPLAYENGINE_SPACE_H

#include <memory>

#include <Window/Window.h>
#include <Window/Camera.h>
#include <Scenes/SceneManager.h>
#include <Core/EngineContext.h>
#include <Window/DesktopData.h>
#include <Scenes/Scene.h>
#include <Time/Clock.h>
#include <Resources/FontManager.h>
#include <Resources/TextureManager.h>

namespace eng {
    class Space
    {
    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<SceneManager> stateManager;
        std::unique_ptr<Clock> clock;
        std::unique_ptr<FontManager> fontManager;
        std::unique_ptr<TextureManager> textureManager;
        std::unique_ptr<EngineContext> ctx;

        bool running = false;

        template<typename StateT, typename... Args>
        void pushState(Args&&... args);
        void popState();
        void draw();

    public:
        //----------------------------------------------------------------------------------------------------------------------
        //Constructors, destructor and intialisation
        //----------------------------------------------------------------------------------------------------------------------
        Space() = delete;
        explicit Space(
            const std::string& title,
            const std::pair<float, float>& worldSize = getDefaultWorldSize(),
            const std::pair<unsigned int, unsigned int>& windowSize = getDefaultWindowSize()
        );

        template<typename StateT, typename... Args>
        void start(Args&&... args);

        void run();

        //----------------------------------------------------------------------------------------------------------------------
        //Setters
        //----------------------------------------------------------------------------------------------------------------------
        void pause();
        void resume();

        //----------------------------------------------------------------------------------------------------------------------
        //Getters
        //----------------------------------------------------------------------------------------------------------------------
        [[nodiscard]] const Scene& getTopState() const;
        [[nodiscard]] const std::vector<std::unique_ptr<Scene>>& getStates() const;
        [[nodiscard]] std::pair<float, float> getSpaceSize();
        [[nodiscard]] float getSpaceWidth();
        [[nodiscard]] float getSpaceHeight();

    };
}
#include "Space.tpp"

#endif