//
// Created by natha on 9/14/2026.
//

#include "Window/DesktopData.h"

std::pair<unsigned int, unsigned int>
getMaxWindowSize(
    const std::pair<float, float>& worldSize
)
{
    // Get the available screen size somehow
    const std::pair<unsigned int, unsigned int> maxWindowSize = getUsableDesktopSize();
    const unsigned int screenWidth = maxWindowSize.first;
    const unsigned int screenHeight = maxWindowSize.second;

    const float worldWidth = worldSize.first;
    const float worldHeight = worldSize.second;

    const float worldAspect = worldWidth / worldHeight;
    const float screenAspect =
        static_cast<float>(screenWidth) / screenHeight;

    unsigned int windowWidth;
    unsigned int windowHeight;

    if (screenAspect > worldAspect)
    {
        // Screen is wider than the world.
        // Height is the limiting dimension.

        windowHeight = screenHeight;
        windowWidth = static_cast<unsigned int>(
            windowHeight * worldAspect
        );
    }
    else
    {
        // Screen is taller/narrower than the world.
        // Width is the limiting dimension.

        windowWidth = screenWidth;
        windowHeight = static_cast<unsigned int>(
            windowWidth / worldAspect
        );
    }

    return {windowWidth, windowHeight};
}

std::pair<unsigned int, unsigned int>
getModestWindowSize(
    const std::pair<float, float>& worldSize
)
{
    const auto maxSize = getMaxWindowSize(worldSize);

    constexpr float scale = 0.75f;

    return {
        static_cast<unsigned int>(maxSize.first * scale),
        static_cast<unsigned int>(maxSize.second * scale)
    };
}

std::pair<unsigned int, unsigned int>
getUsableDesktopSize()
{
    RECT workArea{};

    SystemParametersInfo(
        SPI_GETWORKAREA,
        0,
        &workArea,
        0
    );

    const unsigned int width =
        static_cast<unsigned int>(
            workArea.right - workArea.left
        );

    const unsigned int height =
        static_cast<unsigned int>(
            workArea.bottom - workArea.top
        );

    return {width, height};
}