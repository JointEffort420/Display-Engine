//
// Created by natha on 9/14/2026.
//

#ifndef DISPLAYENGINE_DESKTOPDATA_H
#define DISPLAYENGINE_DESKTOPDATA_H

#include <utility>
#include <windows.h>

namespace eng {
    constexpr float MODEST_WINDOW_SCALE = 0.75f;

    std::pair<unsigned int, unsigned int> getUsableDesktopSize();
    float getDesktopRatio();

    std::pair<float, float> getDefaultWorldSize();
    std::pair<unsigned int, unsigned int> getMaxWindowSize(const std::pair<float, float>& worldSize);

    std::pair<unsigned int, unsigned int> getDefaultWindowSize(const std::pair<float, float>& worldSize);
    std::pair<unsigned int, unsigned int> getDefaultWindowSize();
}

#endif //DISPLAYENGINE_DESKTOPDATA_H