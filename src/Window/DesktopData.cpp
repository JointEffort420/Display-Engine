//
// Created by natha on 9/14/2026.
//

#include "Window/DesktopData.h"

namespace eng {
    //----------------------------------------------------------------------------------------------------------------------
    // Desktop
    //----------------------------------------------------------------------------------------------------------------------
    float getDesktopRatio() {
        const auto [width, height] = getUsableDesktopSize();
        if (height == 0) return 16.0f / 9.0f; // Safe fallback
        return static_cast<float>(width) / static_cast<float>(height);
    }

    std::pair<unsigned int, unsigned int> getUsableDesktopSize() {
        RECT workArea{};
        SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

        const unsigned int width = static_cast<unsigned int>(workArea.right - workArea.left);
        const unsigned int height = static_cast<unsigned int>(workArea.bottom - workArea.top);

        return {width, height};
    }

    //----------------------------------------------------------------------------------------------------------------------
    // World
    //----------------------------------------------------------------------------------------------------------------------
    std::pair<float, float> getDefaultWorldSize() {
        // Standard Engine Convention: Lock height to 1.0f and scale width by desktop aspect ratio
        return {getDesktopRatio(), 1.0f};
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Window
    //----------------------------------------------------------------------------------------------------------------------
    std::pair<unsigned int, unsigned int> getMaxWindowSize(const std::pair<float, float>& worldSize) {
        const auto [screenWidth, screenHeight] = getUsableDesktopSize();

        const float worldWidth = worldSize.first;
        const float worldHeight = worldSize.second;

        // Prevent divide-by-zero
        if (worldHeight <= 0.0f || screenHeight == 0) return {screenWidth, screenHeight};

        const float worldAspect = worldWidth / worldHeight;
        const float screenAspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

        unsigned int windowWidth;
        unsigned int windowHeight;

        if (screenAspect > worldAspect) {
            // Screen is wider than world aspect: height is limiting factor
            windowHeight = screenHeight;
            windowWidth = static_cast<unsigned int>(windowHeight * worldAspect);
        } else {
            // Screen is taller than world aspect: width is limiting factor
            windowWidth = screenWidth;
            windowHeight = static_cast<unsigned int>(windowWidth / worldAspect);
        }

        return {windowWidth, windowHeight};
    }

    std::pair<unsigned int, unsigned int> getDefaultWindowSize(const std::pair<float, float>& worldSize) {
        const auto maxSize = getMaxWindowSize(worldSize);
        return {
            static_cast<unsigned int>(maxSize.first * MODEST_WINDOW_SCALE),
            static_cast<unsigned int>(maxSize.second * MODEST_WINDOW_SCALE)
        };
    }

    std::pair<unsigned int, unsigned int> getDefaultWindowSize() {
        return getDefaultWindowSize(getDefaultWorldSize());
    }
}