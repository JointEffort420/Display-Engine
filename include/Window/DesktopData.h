//
// Created by natha on 9/14/2026.
//

#ifndef DISPLAYENGINE_DESKTOPDATA_H
#define DISPLAYENGINE_DESKTOPDATA_H

#include <utility>
#include <windows.h>

constexpr float MODEST_WINDOW_SCALE = 0.75f;

std::pair<unsigned int, unsigned int> getMaxWindowSize(const std::pair<float, float>& worldSize);
std::pair<unsigned int, unsigned int> getModestWindowSize(const std::pair<float, float>& worldSize);
std::pair<unsigned int, unsigned int> getUsableDesktopSize();

#endif //DISPLAYENGINE_DESKTOPDATA_H